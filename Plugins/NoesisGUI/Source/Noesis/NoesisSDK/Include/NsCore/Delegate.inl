////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


namespace Noesis
{

template<class Ret, class ...Args>
class DelegateImpl<Ret (Args...)>
{
public:
    typedef Noesis::Delegate<Ret (Args...)> Delegate;
    typedef typename Delegate::Invoker Invoker;

    enum Type
    {
        Type_Null,
        Type_FreeFunc,
        Type_Functor,
        Type_FunctorRef,
        Type_MemberFunc,
        Type_MultiDelegate
    };

    struct Base;

    /// Instead of relying on virtual functions, we implement our own virtual table.
    /// This allows us to use special values in the virtual table pointer to identify
    /// Null and MultiDelegates (0x0 for Nulland 0x1 for MultiDelegate)
    struct VTable
    {
        Type (*GetType)();
        bool (*Equal)(const void*, const Base* base, Type type);
        Ret (*Invoke)(const void*, Args&&... args);
        void (*Copy)(void*, Base* dest, bool move);
        void (*Destroy)(void*);
    };

    struct Base
    {
        Type GetType() const
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return Type_Null;
                case 1: return Type_MultiDelegate;
                default: return vTable->GetType();
            }
        }

        uint32_t Size() const
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return 0;
                case 1: return MultiDelegate::Size((MultiDelegate*)this);
                default: return 1;
            }
        }

        bool Equal(const Base* base) const
        {
            return Equal(base, base->GetType());
        }

        bool Equal(const Base* base, Type type) const
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return type == Type_Null;
                case 1: return MultiDelegate::Equal((const MultiDelegate*)this, base, type);
                default: return vTable->Equal(this, base, type);
            }
        }

        Ret Invoke(Args&&... args) const
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return Ret();
                case 1: return MultiDelegate::Invoke((const MultiDelegate*)this, ForwardArg<Args>(args)...);
                default: return vTable->Invoke(this, ForwardArg<Args>(args)...);
            }
        }

        Invoker* GetInvoker() const
        {
            switch ((uintptr_t)vTable)
            {
                case 1: return MultiDelegate::GetInvoker((const MultiDelegate*)this);
                default: return nullptr;
            }
        }

        void Copy(Base* dest, bool move)
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return NullStub::Copy(dest);;
                case 1: return MultiDelegate::Copy((MultiDelegate*)this, dest, move);
                default: return vTable->Copy(this, dest, move);
            }
        }

        void Add(const Delegate& d)
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return NullStub::Add((NullStub*)this, d);
                case 1: return MultiDelegate::Add((MultiDelegate*)this, d);
                default: return SingleDelegate::Add((SingleDelegate*)this, d);
            }
        }

        void Remove(const Delegate& d)
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return;
                case 1: return MultiDelegate::Remove((MultiDelegate*)this, d);
                default: return SingleDelegate::Remove((SingleDelegate*)this, d);
            }
        }

        void Destroy()
        {
            switch ((uintptr_t)vTable)
            {
                case 0: return;
                case 1: return MultiDelegate::Destroy((MultiDelegate*)this);
                default: return vTable->Destroy(this);
            }
        }

        VTable* vTable;
    };

    /// Implementation for null delegates
    class NullStub final: public Base
    {
    public:
        NullStub() { Base::vTable = nullptr; }

        static void Copy(Base* dest) { new(Placement(), dest) NullStub(); }

        static void Add(NullStub* this_, const Delegate& d)
        {
            if (!d.Empty())
            {
                ((Delegate&)d).GetBase()->Copy(this_, false);
            }
        }
    };

    /// Base class implementation for single delegates
    class SingleDelegate: public Base
    {
    public:
        static void Add(SingleDelegate* this_, const Delegate& d)
        {
            if (!d.Empty())
            {
                Delegate self(this_, Int2Type<0>());
                this_->~SingleDelegate();

                MultiDelegate* x = new(Placement(), this_) MultiDelegate();
                MultiDelegate::Add(x, self);
                MultiDelegate::Add(x, d);
            }
        }

        static void Remove(SingleDelegate* this_, const Delegate& d)
        {
            if (this_->Equal(d.GetBase()))
            {
                this_->~SingleDelegate();
                new(Placement(), this_) NullStub();
            }
        }
    };

    /// Implementation for free functions
    template<class Func> class FreeFuncStub final: public SingleDelegate
    {
    public:
        static VTable* GetVTable()
        {
            static VTable table =
            {
                &FreeFuncStub::GetType,
                &FreeFuncStub::Equal,
                &FreeFuncStub::Invoke,
                &FreeFuncStub::Copy,
                &FreeFuncStub::Destroy,
            };

            return &table;
        }

        FreeFuncStub(Func func): mFunc(func)
        {
            Base::vTable = GetVTable();
        }

        static void Destroy(void*) {}

        static Type GetType()
        {
            return Type_FreeFunc;
        }

        static bool Equal(const void* this_, const Base* base, Type type)
        {
            const FreeFuncStub* stub = (const FreeFuncStub*)base;
            return Type_FreeFunc == type && ((FreeFuncStub*)this_)->mFunc == stub->mFunc;
        }

        static Ret Invoke(const void* this_, Args&&... args)
        {
            return ((const FreeFuncStub*)this_)->mFunc(ForwardArg<Args>(args)...);
        }

        static void Copy(void* this_, Base* dest, bool)
        {
            new(Placement(), dest) FreeFuncStub(*((FreeFuncStub*)this_));
        }

    private:
        Func mFunc;
    };

    /// Implementation for functors
    template<class F> class FunctorStub final: public SingleDelegate
    {
    public:
        static VTable* GetVTable()
        {
            static VTable table =
            {
                &FunctorStub::GetType,
                &FunctorStub::Equal,
                &FunctorStub::Invoke,
                &FunctorStub::Copy,
                &FunctorStub::Destroy
            };

            return &table;
        }

        FunctorStub(const F& f): mFunctor(f)
        {
            Base::vTable = GetVTable();
        }

        static void Destroy(void* this_)
        {
            NS_UNUSED(this_);
            ((FunctorStub*)this_)->~FunctorStub();
        }

        static Type GetType()
        {
            return Type_Functor;
        }

        static bool Equal(const void*, const Base*, Type)
        {
            return false;
        }

        static Ret Invoke(const void* this_, Args&&... args)
        {
            const FunctorStub* func = (const FunctorStub*)this_;
            return ((F*)&(func->mFunctor))->operator()(ForwardArg<Args>(args)...);
        }

        static void Copy(void* this_, Base* dest, bool move)
        {
            FunctorStub* func = (FunctorStub*)this_;

            if (!move)
            {
                new(Placement(), dest) FunctorStub(*func);
            }
            else
            {
                new(Placement(), dest) FunctorStub(MoveArg(*func));
                func->~FunctorStub();
                new(Placement(), func) NullStub();
            }
        }

    private:
        F mFunctor;
    };

    /// Implementation for functors ref
    template<class F> class FunctorRefStub final: public SingleDelegate
    {
    public:
        static VTable* GetVTable()
        {
            static VTable table =
            {
                &FunctorRefStub::GetType,
                &FunctorRefStub::Equal,
                &FunctorRefStub::Invoke,
                &FunctorRefStub::Copy,
                &FunctorRefStub::Destroy
            };

            return &table;
        }

        FunctorRefStub(const F* f): mFunctor(f)
        {
            Base::vTable = GetVTable();
        }

        static void Destroy(void*) {}

        static Type GetType()
        {
            return Type_FunctorRef;
        }

        static bool Equal(const void* this_, const Base* base, Type type)
        {
            const FunctorRefStub* stub = (const FunctorRefStub*)base;
            return Type_FunctorRef == type && ((FunctorRefStub*)this_)->mFunctor == stub->mFunctor;
        }

        static Ret Invoke(const void* this_, Args&&... args)
        {
            const FunctorRefStub* func = (const FunctorRefStub*)this_;
            return ((F*)func->mFunctor)->operator()(ForwardArg<Args>(args)...);
        }

        static void Copy(void* this_, Base* dest, bool)
        {
            new(Placement(), dest) FunctorRefStub(*((FunctorRefStub*)this_));
        }

    private:
        const F* mFunctor;
    };

    /// Implementation for member functions
    template<class C, class Func> class MemberFuncStub final: public SingleDelegate
    {
    public:
        static VTable* GetVTable()
        {
            static VTable table =
            {
                &MemberFuncStub::GetType,
                &MemberFuncStub::Equal,
                &MemberFuncStub::Invoke,
                &MemberFuncStub::Copy,
                &MemberFuncStub::Destroy,
            };

            return &table;
        }

        MemberFuncStub(C* obj, Func func) : mObj(obj), mFunc(func)
        {
            Base::vTable = GetVTable();
        }

        static void Destroy(void*) {}

        static Type GetType()
        {
            return Type_MemberFunc;
        }

        static bool Equal(const void* this_, const Base* base, Type type)
        {
            MemberFuncStub* func = (MemberFuncStub*)this_;
            const MemberFuncStub* memFunc = (const MemberFuncStub*)base;
            return Type_MemberFunc == type && func->mObj == memFunc->mObj && func->mFunc == memFunc->mFunc;
        }

        static Ret Invoke(const void* this_, Args&&... args)
        {
            const MemberFuncStub* func = (const MemberFuncStub*)this_;
            return (func->mObj->*(func->mFunc))(ForwardArg<Args>(args)...);
        }

        static void Copy(void* this_, Base* dest, bool)
        {
            new(Placement(), dest) MemberFuncStub(*((MemberFuncStub*)this_));
        }

    protected:
        C* mObj;
        Func mFunc;
    };

    /// Implementation for MultiDelegates
    class MultiDelegate final: public Base
    {
    public:
        MultiDelegate(): mInvoker(MakePtr<Invoker>())
        {
            Base::vTable = (VTable*)0x1;
        }

        MultiDelegate(const MultiDelegate& d): mInvoker(MakePtr<Invoker>())
        {
            mInvoker->v = d.mInvoker->v;
            Base::vTable = (VTable*)0x1;
        }

        MultiDelegate(MultiDelegate&& d): mInvoker(MoveArg(d.mInvoker))
        {
            Base::vTable = (VTable*)0x1;
        }

        static void Destroy(MultiDelegate* this_)
        {
            this_->~MultiDelegate();
        }

        static uint32_t Size(const MultiDelegate* this_)
        {
            Invoker* invoker = this_->mInvoker;
            return invoker->v.Size() - invoker->pendingDeletes;
        }

        static bool Equal(const MultiDelegate* this_, const Base* base, Type type)
        {
            if (Type_MultiDelegate == type)
            {
                const MultiDelegate* x = (const MultiDelegate*)base;
                return this_->mInvoker->v == x->mInvoker->v;
            }

            return false;
        }

        struct InvokerGuard
        {
            InvokerGuard(Invoker* invoker): _invoker(invoker)
            {
                _invoker->BeginInvoke();
            }

            ~InvokerGuard()
            {
                _invoker->EndInvoke();
            }

            Invoker* _invoker;
        };

        static Ret Invoke(const MultiDelegate* this_, Args&&... args)
        {
            Invoker* invoker = this_->mInvoker;
            uint32_t numDelegates = invoker->Size();

            if (numDelegates == 0)
            {
                return Ret();
            }
            else
            {
                InvokerGuard guard(invoker);

                for (uint32_t i = 0; i < numDelegates - 1; ++i)
                {
                    invoker->Invoke(i, ForwardArg<Args>(args)...);
                }

                // last delegate is used to return a value
                return invoker->Invoke(numDelegates - 1, ForwardArg<Args>(args)...);
            }
        }

        static void Copy(MultiDelegate* this_, Base* dest, bool move)
        {
            if (!move)
            {
                new(Placement(), dest) MultiDelegate(*this_);
            }
            else
            {
                new(Placement(), dest) MultiDelegate(MoveArg(*this_));
                this_->~MultiDelegate();
                new(Placement(), this_) NullStub();
            }
        }

        static void Add(MultiDelegate* this_, const Delegate& d)
        {
            if (!d.Empty())
            {
                this_->mInvoker->v.PushBack(d);
            }
        }

        static void Remove(MultiDelegate* this_, const Delegate& d)
        {
            if (!d.Empty())
            {
                Invoker* invoker = this_->mInvoker;
                Delegate* first = invoker->v.Begin();
                const Delegate* last = invoker->v.End();

                const Base* base = d.GetBase();
                Type type = base->GetType();

                while (first != last)
                {
                    if (!first->IsNull())
                    {
                        if (first->GetBase()->Equal(base, type))
                        {
                            first->Reset();
                            invoker->pendingDeletes++;
                            invoker->Compact();
                            return;
                        }
                    }

                    first++;
                }
            }
        }

        static Invoker* GetInvoker(const MultiDelegate* this_)
        {
            return this_->mInvoker;
        }

    private:
        Ptr<Invoker> mInvoker;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::Delegate()
{
    InitNull();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::Delegate(Ret (*func)(Args...))
{
    FromFreeFunc(func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class F, class>
inline Delegate<Ret (Args...)>::Delegate(const F& f)
{
    FromFunctor(f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class F, class>
inline Delegate<Ret (Args...)>::Delegate(const F* f)
{
    FromFunctorRef(f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C> 
inline Delegate<Ret (Args...)>::Delegate(C* obj, Ret (C::*func)(Args...))
{
    FromMemberFunc(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C> 
inline Delegate<Ret (Args...)>::Delegate(const C* obj, Ret (C::*func)(Args...) const)
{
    FromMemberFunc(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C> 
inline Delegate<Ret (Args...)>::Delegate(const Ptr<C>& obj, Ret (C::*func)(Args...))
{
    FromMemberFunc(obj.GetPtr(), func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C> 
inline Delegate<Ret (Args...)>::Delegate(const Ptr<C>& obj, Ret (C::*func)(Args...) const)
{
    FromMemberFunc(obj.GetPtr(), func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C> 
inline Delegate<Ret (Args...)>::Delegate(const Ptr<const C>& obj, Ret (C::*func)(Args...) const)
{
    FromMemberFunc(obj.GetPtr(), func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::Delegate(const Delegate& d)
{
    ((Delegate&)d).GetBase()->Copy(GetBase(), false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::Delegate(Delegate&& d)
{
    d.GetBase()->Copy(GetBase(), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::~Delegate()
{
    GetBase()->Destroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>& Delegate<Ret (Args...)>::operator=(const Delegate& d)
{
    if (this != &d)
    {
        GetBase()->Destroy();
        ((Delegate&)d).GetBase()->Copy(GetBase(), false);
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>& Delegate<Ret (Args...)>::operator=(Delegate&& d)
{
    if (this != &d)
    {
        GetBase()->Destroy();
        d.GetBase()->Copy(GetBase(), true);
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Reset()
{
    GetBase()->Destroy();
    InitNull();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline bool Delegate<Ret (Args...)>::Empty() const
{
    return GetBase()->Size() == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::operator bool() const
{
    return GetBase()->Size() != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline bool Delegate<Ret (Args...)>::operator==(const Delegate& d) const
{
    return GetBase()->Equal(d.GetBase());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline bool Delegate<Ret (Args...)>::operator!=(const Delegate& d) const
{
    return !(GetBase()->Equal(d.GetBase()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Add(const Delegate& d)
{
    GetBase()->Add(d);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::operator+=(const Delegate& d)
{
    GetBase()->Add(d);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Remove(const Delegate& d)
{
    GetBase()->Remove(d);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::operator-=(const Delegate& d)
{
    GetBase()->Remove(d);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline uint32_t Delegate<Ret (Args...)>::Size() const
{
    return GetBase()->Size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Ret Delegate<Ret (Args...)>::operator()(Args... args) const
{
    return GetBase()->Invoke(ForwardArg<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Ret Delegate<Ret (Args...)>::Invoke(Args... args) const
{
    return GetBase()->Invoke(ForwardArg<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline uint32_t Delegate<Ret (Args...)>::Invoker::Size() const
{
    return v.Size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Invoker::BeginInvoke()
{
    AddReference();
    nestingCount++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Ret Delegate<Ret (Args...)>::Invoker::Invoke(uint32_t i, Args... args) const
{
    return (v[i])(ForwardArg<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Invoker::EndInvoke()
{
    nestingCount--;
    Compact();
    Release();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::Invoker::Compact()
{
    if (NS_UNLIKELY(nestingCount == 0 && pendingDeletes > v.Size() / 4))
    {
        v.EraseIf([](const Delegate& d) { return d.IsNull(); });
        pendingDeletes = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline typename Delegate<Ret (Args...)>::Invoker* Delegate<Ret (Args...)>::GetInvoker() const
{
    return GetBase()->GetInvoker();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::FromFreeFunc(Ret (*func)(Args...))
{
    typedef typename Impl::template FreeFuncStub<Ret (*)(Args...)> T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T(func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class F>
inline void Delegate<Ret (Args...)>::FromFunctor(const F& f)
{
    typedef typename Impl::template FunctorStub<F> T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T(f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class F>
inline void Delegate<Ret (Args...)>::FromFunctorRef(const F* f)
{
    typedef typename Impl::template FunctorRefStub<F> T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T(f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C>
inline void Delegate<Ret (Args...)>::FromMemberFunc(C* obj, Ret (C::*func)(Args...))
{
    typedef typename Impl::template MemberFuncStub<C, Ret (C::*)(Args...)> T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
template<class C>
inline void Delegate<Ret (Args...)>::FromMemberFunc(const C* obj, Ret (C::*func)(Args...) const)
{
    typedef typename Impl::template MemberFuncStub<C, Ret (C::*)(Args...) const> T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T(const_cast<C*>(obj), func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline void Delegate<Ret (Args...)>::InitNull()
{
    typedef typename Impl::NullStub T;
    static_assert(sizeof(T) <= sizeof(data), "Insufficient buffer size");
    new(Placement(), data) T();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline bool Delegate<Ret (Args...)>::IsNull() const
{
    return ((typename Impl::NullStub*)GetBase())->vTable == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline typename Delegate<Ret (Args...)>::Impl::Base* Delegate<Ret (Args...)>::GetBase()
{
    return (typename Impl::Base*)data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline const typename Delegate<Ret (Args...)>::Impl::Base* Delegate<Ret (Args...)>::GetBase() const
{
    return (const typename Impl::Base*)data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
inline Delegate<Ret (Args...)>::Delegate(typename Impl::Base* base, Int2Type<0>)
{
    base->Copy(GetBase(), false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret , class ...Args>
inline Delegate<Ret (Args...)> MakeDelegate(C* obj, Ret (C::*func)(Args...))
{
    return Delegate<Ret (Args...)>(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret, class ...Args>
inline Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*func)(Args...))
{
    return Delegate<Ret (Args...)>(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret, class ...Args>
inline Delegate<Ret (Args...)> MakeDelegate(const C* obj, Ret (C::*func)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret, class ...Args>
inline Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*func)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret, class ...Args>
inline Delegate<Ret (Args...)> MakeDelegate(const Ptr<const C>& obj, Ret (C::*func)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, func);
}

}
