// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTextActor.generated.h"

UCLASS(Abstract)
class TURNBASED_API AFloatingTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingTextActor();
	
	//Initializes the actor with the required starting information
	UFUNCTION(BlueprintImplementableEvent, Category = "FloatingTextActor")
	void Initialize(const FText& Text, FLinearColor TextColor);

	//Get the anchor location
	inline const FVector& GetAnchorPoint() const { return AnchorLocation; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//The location to which the text is anchored
	FVector AnchorLocation;
};
