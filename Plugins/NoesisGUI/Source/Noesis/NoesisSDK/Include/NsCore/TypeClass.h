////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASS_H__
#define __CORE_TYPECLASS_H__


#include <NsCore/Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeMeta.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

class TypeProperty;
class Symbol;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClass. Defines reflection info for structs and classes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeClass: public TypeMeta
{
public:
    /// Constructor
    TypeClass(Symbol name, bool isInterface);

    /// Destructor
    ~TypeClass();

    /// Custom allocators
    static void* operator new(SizeT size);
    static void operator delete(void* ptr, SizeT size);

    /// Defines ancestor information
    struct AncestorInfo
    {
        /// reflection type of ancestor class
        const TypeClass* type;

        /// offset from the implementation class pointer to the ancestor
        uint32_t offset;

        /// Constructor
        AncestorInfo(const TypeClass* t, uint32_t o): type(t), offset(o) { }
    };

    /// Gets base implementation class type
    const TypeClass* GetBase() const;

    /// Gets number of interfaces this class implements
    uint32_t GetNumInterfaces() const;

    /// Gets info about an interface implemented by this class
    const AncestorInfo* GetInterface(uint32_t index) const;

    /// Tells if this type represents an interface
    bool IsInterface() const;

    /// Determines if this class is a descendant of the specified type.
    bool IsDescendantOf(const TypeClass* ancestorType) const;

    /// Gets info about an ancestor
    const AncestorInfo* GetAncestorInfo(const TypeClass* ancestorType) const;

    /// Gets number of properties of this class reflection type
    uint32_t GetNumProperties() const;

    /// Gets a property of the reflection type
    const TypeProperty* GetProperty(uint32_t index) const;

    /// Looks for a property given its name. If this class type has the property requested then it
    /// returns the property, else it returns a null pointer.
    const TypeProperty* FindProperty(Symbol name) const;

    /// Gets number of events of this class reflection type
    uint32_t GetNumEvents() const;

    /// Gets an event of the reflection type
    const TypeProperty* GetEvent(uint32_t index) const;

    /// Indicates if this class type has the specified event
    const TypeProperty* FindEvent(Symbol name) const;

    /// From Type
    //@{
    bool IsAssignableFrom(const Type* type) const override;
    //@}

    /// Deallocates all internal memory
    static void Shutdown();

protected:
    bool mIsInterface;

    // Implementation base class
    const TypeClass* mBase;

    // List of interfaces implemented by this class
    typedef Vector<AncestorInfo> AncestorVector;
    AncestorVector mInterfaces;

    typedef Vector<TypeProperty*> PropertyVector;
    PropertyVector mProperties;

    typedef Vector<TypeProperty*> EventVector;
    EventVector mEvents;

protected:
    void ClearAncestorsCache() const;

private:
    void CacheAncestors() const;
    void CacheBase(const TypeClass* type) const;
    void CacheInterface(const TypeClass* type, uint32_t offset) const;

private:
    mutable void* mAncestorsCache;

    NS_DECLARE_REFLECTION(TypeClass, TypeMeta)
};

NS_WARNING_POP

}

#endif
