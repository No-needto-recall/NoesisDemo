////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DELEGATE_H__
#define __CORE_DELEGATE_H__


#include <NsCore/Noesis.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Vector.h>
#include <NsCore/Ptr.h>


namespace Noesis
{

template<class T> class Delegate;
template<class T> class DelegateImpl;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A generic and efficient implementation of callbacks, an alternative to std::function:
///
/// Advantages:
/// - Faster compilation times compared to std::function
/// - Easier to debug due to simpler internal structure
/// - Fixed memory footprint (4 pointers), with no heap allocations
/// - Supports multicast (like C#) via '+=' operator (note: multicast uses dynamic memory)
/// - Delegates are comparable (e.g., for removing handlers)
///
/// Lambda Support:
/// - Standard C++ lambdas **cannot be compared** (due to unique closure types)
/// - However, we support 'lambda_ref' delegates, which store a pointer to the lambda
///   - These *can* be compared
///   - They can be used with '+=' and '-=' for multicast registration/removal
///   - The caller is responsible for keeping the lambda alive for the lifetime of the delegate
///
/// Usage Examples:
///   Delegate<uint32_t (uint32_t)> d0 = &MyReporter;
///   Delegate<uint32_t (uint32_t)> d1 = MakeDelegate(obj, &Manager::MyReporter)
///   Delegate<uint32_t (uint32_t)> d2 = [](uint32_t x) { return x + 1; };
///
///   auto lambda = [](uint32_t) { return 0; };
///   Delegate<uint32_t (uint32_t)> d3 = &lambda;
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
class Delegate<Ret (Args...)>
{
public:
    /// Constructor for empty delegates
    Delegate();

    /// Constructor from free function
    Delegate(Ret (*func)(Args...));

    /// Constructs a delegate from a lambda or functor
    /// The lambda cannot be compared, so it cannot be removed from a multicast delegate
    template<class F, class = EnableIf<IsInvocable<decltype(&F::operator()), Ret, Args...>::Result>>
    Delegate(const F& f);

    /// Constructs a delegate from a lambda or functor pointer (similar to 'std::function_ref')
    /// This allows comparison, so the delegate can be removed from a multicast delegate
    template<class F, class = EnableIf<IsInvocable<decltype(&F::operator()), Ret, Args...>::Result>>
    Delegate(const F* f);

    /// Constructor from class member function
    template<class C> Delegate(C* obj, Ret (C::*func)(Args...));

    /// Constructor from class member function (const)
    template<class C> Delegate(const C* obj, Ret (C::*func)(Args...) const);

    /// Constructor from ref-counted class member function
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*func)(Args...));

    /// Constructor from ref-counted class member function (const)
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*func)(Args...) const);

    /// Constructor from ref-counted class member function (const)
    template<class C> Delegate(const Ptr<const C>& obj, Ret (C::*func)(Args...) const);

    /// Copy constructor
    Delegate(const Delegate& d);

    /// Move constructor
    Delegate(Delegate&& d);

    /// Destructor
    ~Delegate();

    /// Copy operator
    Delegate& operator=(const Delegate& d);

    /// Move operator
    Delegate& operator=(Delegate&& d);

    /// Reset to empty
    void Reset();

    /// Check if delegate is empty
    bool Empty() const;

    /// Boolean conversion
    operator bool() const;

    /// Equality
    bool operator==(const Delegate& d) const;

    /// Non-equality
    bool operator!=(const Delegate& d) const;

    /// Add delegate
    void Add(const Delegate& d);
    void operator+=(const Delegate& d);

    /// Remove delegate
    void Remove(const Delegate& d);
    void operator-=(const Delegate& d);

    /// Numbers of contained delegates
    uint32_t Size() const;

    /// Delegate invocation. For multidelegates, returned value corresponds to last invocation
    Ret operator()(Args... args) const;
    Ret Invoke(Args... args) const;

    /// Delegate invoker for manual invocations of multidelegates items
    struct Invoker: public BaseComponent
    {
        uint32_t Size() const;

        void BeginInvoke();
        Ret Invoke(uint32_t i, Args... args) const;
        void EndInvoke();

        void Compact();

        uint16_t nestingCount = 0;
        uint16_t pendingDeletes = 0;
        Vector<Delegate, 2> v;
    };

    /// Returns the invoker of the delegate, or null for simple delegates
    Invoker* GetInvoker() const;

private:
    void FromFreeFunc(Ret (*func)(Args...));
    template<class F> void FromFunctor(const F& f);
    template<class F> void FromFunctorRef(const F* f);
    template<class C> void FromMemberFunc(C* obj, Ret (C::*func)(Args...));
    template<class C> void FromMemberFunc(const C* obj, Ret (C::*func)(Args...) const);

    void InitNull();
    bool IsNull() const;

    typedef DelegateImpl<Ret (Args...)> Impl;
    friend Impl;

    typename Impl::Base* GetBase();
    const typename Impl::Base* GetBase() const;

    Delegate(typename Impl::Base* base, Int2Type<0>);

private:
    alignas(void*) uint8_t data[4 * sizeof(void*)];
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper functions to deduce automatically the type when creating a delegate
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret , class ...Args>
Delegate<Ret (Args...)> MakeDelegate(C* obj, Ret (C::*func)(Args...));

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*func)(Args...));

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const C* obj, Ret (C::*func)(Args...) const);

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*func)(Args...) const);

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<const C>& obj, Ret (C::*func)(Args...) const);

}

#include <NsCore/Delegate.inl>

#endif
