// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTextComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "FloatingTextActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFloatingTextComponent::UFloatingTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFloatingTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

	//Check for bad viewport size
	if (ViewportSize.X <= 0.0f || ViewportSize.Y <= 0.0f)
	{
		return;
	}

	//Get the viewport scale (DPI Scale)
	const int32 ViewportX = FGenericPlatformMath::FloorToInt(ViewportSize.X);
	const int32 ViewportY = FGenericPlatformMath::FloorToInt(ViewportSize.Y);
	const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportX, ViewportY));

	if (ViewportScale <= 0.0f)
	{
		return;
	}

	//Get the owning player camera location
	if (GetOwner<APawn>()->GetController<APlayerController>() == nullptr)
	{
		return;
	}

	const FVector CameraLocation = GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->GetCameraLocation();

	//Adjust the vertical location of the text actor by the viewport size and scale so they appear evenly stacked
	for (int32 i = 1; i < ActiveTextActors.Num(); i++)
	{
		//Calculate the vertical offset based on how far we are from the floating text actor
		AFloatingTextActor* TextActor = ActiveTextActors[i];
		const float Distance = FVector::Dist(CameraLocation, TextActor->GetAnchorPoint());
		const float VerticalOffset = Distance / (ViewportSize.X / ViewportScale);

		//Adjust the floating text actor position
		TextActor->SetActorLocation(TextActor->GetAnchorPoint() + FVector(0.0f, 0.0f, i * VerticalOffset * TextVerticalSpacing));
	}
}

void UFloatingTextComponent::AddFloatingText(const FText& Text, FVector WorldLocation, FLinearColor TextColor)
{
	if (FloatingTextActorClass == nullptr)
	{
		return;
	}
	//Spawn new text actor at specified location
	const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation + FVector(0.0f, 0.0f, TextVerticalOffset));
	AFloatingTextActor* NewTextActor = GetWorld()->SpawnActorDeferred<AFloatingTextActor>(FloatingTextActorClass, SpawnTransform, GetOwner());
	if (NewTextActor == nullptr)
	{
		return;
	}
	//Initialize and finish spawning the actor
	NewTextActor->Initialize(Text, TextColor);
	NewTextActor->OnDestroyed.AddDynamic(this, &UFloatingTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(NewTextActor, SpawnTransform);

	//Add the new text actor the start of the active text actor array
	ActiveTextActors.Insert(NewTextActor, 0);
}

void UFloatingTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveTextActors.Pop();
}

