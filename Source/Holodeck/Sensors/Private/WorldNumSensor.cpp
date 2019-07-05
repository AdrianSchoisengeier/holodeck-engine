// Fill out your copyright notice in the Description page of Project Settings.

#include "Holodeck.h"
#include "WorldNumSensor.h"
#include "HolodeckGameMode.h"

UWorldNumSensor::UWorldNumSensor() {
	PrimaryComponentTick.bCanEverTick = true;
	SensorName = "WorldNumSensor";
}

void UWorldNumSensor::InitializeSensor() {
	Super::InitializeSensor();
}

void UWorldNumSensor::ParseSensorParms(FString ParmsJson) {
	Super::ParseSensorParms(ParmsJson);

	TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ParmsJson);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {

		if (JsonParsed->HasTypedField<EJson::String>("Key")) {
			Key = JsonParsed->GetStringField("Key");
		}
	}
	else {
		UE_LOG(LogHolodeck, Warning, TEXT("UWorldNumSensor::ParseSensorParms:: Unable to parse json."));
	}
}

void UWorldNumSensor::TickSensorComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	//Check if the sensor is on and if it is retrieve the ball location from the world state
	if (bOn) {
		AActor* Target = GetWorld()->GetAuthGameMode();
		AHolodeckGameMode* Game = static_cast<AHolodeckGameMode*>(Target);
		int* IntBuffer = static_cast<int*>(Buffer);
		IntBuffer[0] = (int32)Game->GetWorldNum(Key);
	}
}
