// Fill out your copyright notice in the Description page of Project Settings.

#include "NoesisNotifyHelperLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogNoesisNotifyHelper, Log, All);

// 声明 NoesisGUI 官方通知函数
extern NOESISRUNTIME_API void NoesisNotifyPropertyChanged(UObject* Owner, FName PropertyName);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyChanged(UObject* Owner, FName ArrayPropertyName);
extern NOESISRUNTIME_API void NoesisNotifyMapPropertyChanged(UObject* Owner, FName MapPropertyName);
extern NOESISRUNTIME_API void NoesisNotifyCanExecuteFunctionChanged(UObject* Owner, FName CommandName);

extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostAdd(void* Array);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPreAppend(void* Array);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostAppend(void* Array);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostInsert(void* Array, int32 Index);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPreRemove(void* Array, int32 Index);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostRemove(void* Array, int32 Index);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPreSet(void* Array, int32 Index);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostSet(void* Array, int32 Index);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostClear(void* Array);
extern NOESISRUNTIME_API void NoesisNotifyArrayPropertyPostReset(void* Array);

extern NOESISRUNTIME_API void NoesisNotifyMapPropertyPostAdd(void* Map, const FString& Key);
extern NOESISRUNTIME_API void NoesisNotifyMapPropertyPreRemove(void* Map, const FString& Key);
extern NOESISRUNTIME_API void NoesisNotifyMapPropertyPostRemove(void* Map, const FString& Key);
extern NOESISRUNTIME_API void NoesisNotifyMapPropertyPostChanged(void* Map);
extern NOESISRUNTIME_API void NoesisNotifyMapPropertyPostReset(void* Map);

// ==================== 基础通知函数实现 ====================

void UNoesisNotifyHelperLibrary::NotifyPropertyChanged(const UObject* Target, const FName& PropertyName)
{
	if (!Target)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("NotifyPropertyChanged: Target is null"));
		return;
	}

	NoesisNotifyPropertyChanged(const_cast<UObject*>(Target), PropertyName);
}

void UNoesisNotifyHelperLibrary::NotifyArrayChanged(const UObject* Target, const FName& ArrayPropertyName)
{
	if (!Target)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("NotifyArrayChanged: Target is null"));
		return;
	}

	NoesisNotifyArrayPropertyChanged(const_cast<UObject*>(Target), ArrayPropertyName);
}

void UNoesisNotifyHelperLibrary::NotifyMapChanged(const UObject* Target, const FName& MapPropertyName)
{
	if (!Target)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("NotifyMapChanged: Target is null"));
		return;
	}

	NoesisNotifyMapPropertyChanged(const_cast<UObject*>(Target), MapPropertyName);
}

void UNoesisNotifyHelperLibrary::NotifyCanExecuteChanged(const UObject* Target, const FName& CommandName)
{
	if (!Target)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("NotifyCanExecuteChanged: Target is null"));
		return;
	}

	NoesisNotifyCanExecuteFunctionChanged(const_cast<UObject*>(Target), CommandName);
}

// ==================== 辅助函数实现 ====================

void* UNoesisNotifyHelperLibrary::GetPropertyAddress(const UObject* Target, const FName& PropertyName, FProperty*& OutProperty)
{
	if (!Target)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("GetPropertyAddress: Target is null"));
		return nullptr;
	}

	OutProperty = Target->GetClass()->FindPropertyByName(PropertyName);
	if (!OutProperty)
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' not found on %s"), 
			*PropertyName.ToString(), *Target->GetClass()->GetName());
		return nullptr;
	}

	return OutProperty->ContainerPtrToValuePtr<void>(const_cast<UObject*>(Target));
}

// ==================== 数组精细操作实现 ====================

bool UNoesisNotifyHelperLibrary::NotifyArrayPostAdd(const UObject* Target, const FName& ArrayPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostAdd(PropertyAddress);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPreAppend(const UObject* Target, const FName& ArrayPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPreAppend(PropertyAddress);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostAppend(const UObject* Target, const FName& ArrayPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostAppend(PropertyAddress);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostInsert(const UObject* Target, const FName& ArrayPropertyName, const int32 Index)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostInsert(PropertyAddress, Index);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPreRemove(const UObject* Target, const FName& ArrayPropertyName, const int32 Index)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPreRemove(PropertyAddress, Index);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostRemove(const UObject* Target, const FName& ArrayPropertyName, const int32 Index)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostRemove(PropertyAddress, Index);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPreSet(const UObject* Target, const FName& ArrayPropertyName, const int32 Index)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPreSet(PropertyAddress, Index);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostSet(const UObject* Target, const FName& ArrayPropertyName, const int32 Index)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostSet(PropertyAddress, Index);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostClear(const UObject* Target, const FName& ArrayPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostClear(PropertyAddress);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyArrayPostReset(const UObject* Target, const FName& ArrayPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, ArrayPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FArrayProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not an array property on %s"), 
			*ArrayPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyArrayPropertyPostReset(PropertyAddress);
	return true;
}

// ==================== Map 精细操作实现 ====================

bool UNoesisNotifyHelperLibrary::NotifyMapPostAdd(const UObject* Target, const FName& MapPropertyName, const FString& Key)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, MapPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FMapProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not a map property on %s"), 
			*MapPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyMapPropertyPostAdd(PropertyAddress, Key);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyMapPreRemove(const UObject* Target, const FName& MapPropertyName, const FString& Key)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, MapPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FMapProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not a map property on %s"), 
			*MapPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyMapPropertyPreRemove(PropertyAddress, Key);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyMapPostRemove(const UObject* Target, const FName& MapPropertyName, const FString& Key)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, MapPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FMapProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not a map property on %s"), 
			*MapPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyMapPropertyPostRemove(PropertyAddress, Key);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyMapPostChanged(const UObject* Target, const FName& MapPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, MapPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FMapProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not a map property on %s"), 
			*MapPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyMapPropertyPostChanged(PropertyAddress);
	return true;
}

bool UNoesisNotifyHelperLibrary::NotifyMapPostReset(const UObject* Target, const FName& MapPropertyName)
{
	FProperty* Property = nullptr;
	void* PropertyAddress = GetPropertyAddress(Target, MapPropertyName, Property);
	
	if (!PropertyAddress || !Property)
	{
		return false;
	}

	if (!Property->IsA<FMapProperty>())
	{
		UE_LOG(LogNoesisNotifyHelper, Warning, TEXT("Property '%s' is not a map property on %s"), 
			*MapPropertyName.ToString(), *Target->GetClass()->GetName());
		return false;
	}
	
	NoesisNotifyMapPropertyPostReset(PropertyAddress);
	return true;
}

