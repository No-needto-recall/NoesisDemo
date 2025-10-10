// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoesisNotifyHelperLibrary.generated.h"

/**
 * NoesisGUI 通知辅助函数库
 * 提供简化的蓝图接口，只需传入 UObject* 和属性名称即可通知 NoesisGUI 更新
 * 
 * 使用场景：
 * 1. 基础通知：直接通知属性/数组/Map 完全改变
 * 2. 精细通知：通知数组/Map 的具体操作（添加、删除、插入等），性能更好
 */
UCLASS()
class NOESISVIEWMODE_API UNoesisNotifyHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ==================== 基础通知函数 ====================
	
	/**
	 * 通知普通属性已更改
	 * 适用于: int32, float, bool, FString, UObject* 等基础类型属性
	 * 
	 * @param Target 目标对象
	 * @param PropertyName 属性名称
	 * 
	 * 示例:
	 *   PlayerData->Health = 100;
	 *   NotifyPropertyChanged(PlayerData, "Health");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify",
		meta = (DefaultToSelf = "Target", Keywords = "notify property changed noesis"))
	static void NotifyPropertyChanged(const UObject* Target, const FName& PropertyName);

	/**
	 * 通知数组属性完全改变
	 * 适用于: 数组内容完全重置或不确定具体操作时使用
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * 
	 * 示例:
	 *   PlayerData->Inventory.Reset();
	 *   NotifyArrayChanged(PlayerData, "Inventory");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify",
		meta = (DefaultToSelf = "Target", Keywords = "notify array changed noesis"))
	static void NotifyArrayChanged(const UObject* Target, const FName& ArrayPropertyName);

	/**
	 * 通知 Map 属性完全改变
	 * 适用于: Map 内容完全重置或不确定具体操作时使用
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * 
	 * 示例:
	 *   PlayerData->Weapons.Reset();
	 *   NotifyMapChanged(PlayerData, "Weapons");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify",
		meta = (DefaultToSelf = "Target", Keywords = "notify map changed noesis"))
	static void NotifyMapChanged(const UObject* Target, const FName& MapPropertyName);

	/**
	 * 通知 Command 的 CanExecute 状态改变
	 * 适用于: 当 Command 的可执行状态发生变化时调用
	 * 
	 * @param Target 目标对象
	 * @param CommandName Command 函数名称
	 * 
	 * 示例:
	 *   PlayerData->CarriedItem = NewItem;
	 *   NotifyCanExecuteChanged(PlayerData, "DropItem");  // 通知 CanExecuteDropItem 状态改变
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify",
		meta = (DefaultToSelf = "Target", Keywords = "notify command canexecute noesis"))
	static void NotifyCanExecuteChanged(const UObject* Target, const FName& CommandName);

	// ==================== 数组精细操作通知（性能更好）====================

	/**
	 * 通知数组末尾添加了元素
	 * 性能优于 NotifyArrayChanged，建议在确定是添加操作时使用
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @return 操作是否成功（属性必须是数组类型）
	 * 
	 * 示例:
	 *   PlayerData->Weapons.Add(NewWeapon);
	 *   NotifyArrayPostAdd(PlayerData, "Weapons");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array add noesis"))
	static bool NotifyArrayPostAdd(const UObject* Target, const FName& ArrayPropertyName);

	/**
	 * 通知数组即将批量追加元素（在追加前调用）
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   NotifyArrayPreAppend(PlayerData, "Inventory");
	 *   PlayerData->Inventory.Append(NewItems);
	 *   NotifyArrayPostAppend(PlayerData, "Inventory");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array append noesis"))
	static bool NotifyArrayPreAppend(const UObject* Target, const FName& ArrayPropertyName);

	/**
	 * 通知数组已批量追加元素（在追加后调用）
	 * 必须与 NotifyArrayPreAppend 配对使用
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @return 操作是否成功
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array append noesis"))
	static bool NotifyArrayPostAppend(const UObject* Target, const FName& ArrayPropertyName);

	/**
	 * 通知数组插入了元素
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @param Index 插入的索引位置
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   PlayerData->Weapons.Insert(NewWeapon, 2);
	 *   NotifyArrayPostInsert(PlayerData, "Weapons", 2);
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array insert noesis"))
	static bool NotifyArrayPostInsert(const UObject* Target, const FName& ArrayPropertyName, const int32 Index);

	/**
	 * 通知数组即将移除元素（在移除前调用）
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @param Index 要移除的索引
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   NotifyArrayPreRemove(PlayerData, "Weapons", 1);
	 *   PlayerData->Weapons.RemoveAt(1);
	 *   NotifyArrayPostRemove(PlayerData, "Weapons", 1);
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array remove noesis"))
	static bool NotifyArrayPreRemove(const UObject* Target, const FName& ArrayPropertyName, const int32 Index);

	/**
	 * 通知数组已移除元素（在移除后调用）
	 * 必须与 NotifyArrayPreRemove 配对使用
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @param Index 已移除的索引
	 * @return 操作是否成功
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array remove noesis"))
	static bool NotifyArrayPostRemove(const UObject* Target, const FName& ArrayPropertyName, const int32 Index);

	/**
	 * 通知数组即将设置元素（在设置前调用）
	 * 用于替换已存在索引的元素
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @param Index 要设置的索引
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   NotifyArrayPreSet(PlayerData, "Weapons", 0);
	 *   PlayerData->Weapons[0] = NewWeapon;
	 *   NotifyArrayPostSet(PlayerData, "Weapons", 0);
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array set noesis"))
	static bool NotifyArrayPreSet(const UObject* Target, const FName& ArrayPropertyName, const int32 Index);

	/**
	 * 通知数组已设置元素（在设置后调用）
	 * 必须与 NotifyArrayPreSet 配对使用
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @param Index 已设置的索引
	 * @return 操作是否成功
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array set noesis"))
	static bool NotifyArrayPostSet(const UObject* Target, const FName& ArrayPropertyName, const int32 Index);

	/**
	 * 通知数组已清空
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   PlayerData->Weapons.Empty();
	 *   NotifyArrayPostClear(PlayerData, "Weapons");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array clear empty noesis"))
	static bool NotifyArrayPostClear(const UObject* Target, const FName& ArrayPropertyName);

	/**
	 * 通知数组已重置
	 * 
	 * @param Target 目标对象
	 * @param ArrayPropertyName 数组属性名称
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   PlayerData->Weapons.Reset();
	 *   NotifyArrayPostReset(PlayerData, "Weapons");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Array",
		meta = (DefaultToSelf = "Target", Keywords = "notify array reset noesis"))
	static bool NotifyArrayPostReset(const UObject* Target, const FName& ArrayPropertyName);

	// ==================== Map 精细操作通知（性能更好）====================
	
	/**
	 * ⚠️ 重要：Noesis 要求 TMap 的 Key 必须是 FString 类型
	 * 其他类型的 Key（如 int32、FName）无法被 Noesis 正确识别
	 */

	/**
	 * 通知 Map 添加了键值对
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * @param Key 添加的键（必须是 FString 类型）
	 * @return 操作是否成功（属性必须是 TMap<FString, T> 类型）
	 * 
	 * 示例:
	 *   PlayerData->Inventory.Add("Sword", SwordItem);
	 *   NotifyMapPostAdd(PlayerData, "Inventory", "Sword");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Map",
		meta = (DefaultToSelf = "Target", Keywords = "notify map add noesis"))
	static bool NotifyMapPostAdd(const UObject* Target, const FName& MapPropertyName, const FString& Key);

	/**
	 * 通知 Map 即将移除键值对（在移除前调用）
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * @param Key 要移除的键（必须是 FString 类型）
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   NotifyMapPreRemove(PlayerData, "Inventory", "Sword");
	 *   PlayerData->Inventory.Remove("Sword");
	 *   NotifyMapPostRemove(PlayerData, "Inventory", "Sword");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Map",
		meta = (DefaultToSelf = "Target", Keywords = "notify map remove noesis"))
	static bool NotifyMapPreRemove(const UObject* Target, const FName& MapPropertyName, const FString& Key);

	/**
	 * 通知 Map 已移除键值对（在移除后调用）
	 * 必须与 NotifyMapPreRemove 配对使用
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * @param Key 已移除的键（必须是 FString 类型）
	 * @return 操作是否成功
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Map",
		meta = (DefaultToSelf = "Target", Keywords = "notify map remove noesis"))
	static bool NotifyMapPostRemove(const UObject* Target, const FName& MapPropertyName, const FString& Key);

	/**
	 * 通知 Map 内容已改变
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * @return 操作是否成功
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Map",
		meta = (DefaultToSelf = "Target", Keywords = "notify map changed noesis"))
	static bool NotifyMapPostChanged(const UObject* Target, const FName& MapPropertyName);

	/**
	 * 通知 Map 已重置
	 * 
	 * @param Target 目标对象
	 * @param MapPropertyName Map 属性名称
	 * @return 操作是否成功
	 * 
	 * 示例:
	 *   PlayerData->Inventory.Reset();
	 *   NotifyMapPostReset(PlayerData, "Inventory");
	 */
	UFUNCTION(BlueprintCallable, Category = "NoesisViewMode|Notify|Map",
		meta = (DefaultToSelf = "Target", Keywords = "notify map reset noesis"))
	static bool NotifyMapPostReset(const UObject* Target, const FName& MapPropertyName);

private:
	/**
	 * 通过反射获取属性地址
	 * @param Target 目标对象
	 * @param PropertyName 属性名称
	 * @param OutProperty 输出属性对象
	 * @return 属性的内存地址，失败返回 nullptr
	 */
	static void* GetPropertyAddress(const UObject* Target, const FName& PropertyName, FProperty*& OutProperty);
};

