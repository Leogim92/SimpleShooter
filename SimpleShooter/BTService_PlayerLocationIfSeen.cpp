// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    if (OwnerComp.GetAIOwner() != nullptr)
    {
        AActor *Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if(Player != nullptr)
        {
            if (OwnerComp.GetAIOwner()->LineOfSightTo(Player))
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Player);
                return;
            }
        }
    }

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}


