// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingTextComponent.generated.h"

class AFloatingTextActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASED_API UFloatingTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingTextComponent();

private:
	//The floating text class to use to display the text
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingTextComponent", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFloatingTextActor> FloatingTextActorClass = nullptr;

	//Amount of vertical space between each damage number
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingTextComponent", Meta = (AllowPrivateAccess = "true"))
	float TextVerticalSpacing = 40.0f;

	//Amount of vertical offset to apply when spawning a new text actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingTextComponent", Meta = (AllowPrivateAccess = "true"))
	float TextVerticalOffset = 100.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Adds the specified text at the specified location in world space
	UFUNCTION(BlueprintCallable, Category = "FloatingTextComponent")
	void AddFloatingText(const FText& Text, FVector WorldLocation, FLinearColor TextColor);

private:
	//Callback for when text actor is destroyed
	UFUNCTION()
	void OnTextDestroyed(AActor* DestroyedActor);

	//An array of all floating text actor
	UPROPERTY()
	TArray<AFloatingTextActor*> ActiveTextActors;
};
