#include "LCJsonHelper.h"
#include "Serialization/JsonWriter.h"

FString FLCJsonHelper::GetJsonString(const TLCMap& Value, bool bNeedNull) {
	FString JsonStr;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	for (auto Tuple : Value)
	{
		if (Tuple.Value.IsIntegerType()) {
			JsonWriter->WriteValue(Tuple.Key, Tuple.Value.AsInteger());
		}
		else if (Tuple.Value.IsDoubleType()) {
			JsonWriter->WriteValue(Tuple.Key, Tuple.Value.AsDouble());
		}
		else if (Tuple.Value.IsBooleanType()) {
			JsonWriter->WriteValue(Tuple.Key, Tuple.Value.AsBoolean());
		}
		else if (Tuple.Value.IsStringType() ||
			Tuple.Value.IsGeoPointType() ||
			Tuple.Value.IsDataType() ||
			Tuple.Value.IsDateType()) {
			JsonWriter->WriteValue(Tuple.Key, Tuple.Value.AsString());
		} else if (bNeedNull && Tuple.Value.IsNoneType()) {
			JsonWriter->WriteNull(Tuple.Key);
		} else if (Tuple.Value.IsMapType()) {
			JsonWriter->WriteRawJSONValue(Tuple.Key, GetJsonString(Tuple.Value.AsMap(), bNeedNull));
		} else if (Tuple.Value.IsObjectType()) {
			JsonWriter->WriteRawJSONValue(Tuple.Key, GetJsonString(Tuple.Value.AsObject(), bNeedNull));
		} else if (Tuple.Value.IsArrayType()) {
			JsonWriter->WriteRawJSONValue(Tuple.Key, GetJsonString(Tuple.Value.AsArray(), bNeedNull));
		}
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	return JsonStr;
}

FString FLCJsonHelper::GetJsonString(const TLCArray& Value, bool bNeedNull) {
	FString JsonStr;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	JsonWriter->WriteArrayStart();
	for (auto SubValue : Value)
	{
		if (SubValue.IsIntegerType()) {
			JsonWriter->WriteValue(SubValue.AsInteger());
		}
		else if (SubValue.IsDoubleType()) {
			JsonWriter->WriteValue(SubValue.AsDouble());
		}
		else if (SubValue.IsBooleanType()) {
			JsonWriter->WriteValue(SubValue.AsBoolean());
		}
		else if (SubValue.IsStringType() ||
			SubValue.IsGeoPointType() ||
			SubValue.IsDataType() ||
			SubValue.IsDateType()) {
			JsonWriter->WriteValue(SubValue.AsString());
			} else if (bNeedNull && SubValue.IsNoneType()) {
				JsonWriter->WriteNull();
			} else if (SubValue.IsMapType()) {
				JsonWriter->WriteRawJSONValue(GetJsonString(SubValue.AsMap(), bNeedNull));
			} else if (SubValue.IsObjectType()) {
				JsonWriter->WriteRawJSONValue(GetJsonString(SubValue.AsObject(), bNeedNull));
			} else if (SubValue.IsArrayType()) {
				JsonWriter->WriteRawJSONValue(GetJsonString(SubValue.AsArray(), bNeedNull));
			}
	}
	JsonWriter->WriteArrayEnd();
	JsonWriter->Close();

	return JsonStr;
}

FString FLCJsonHelper::GetJsonString(const TSharedPtr<FLCObject>& Value, bool bNeedNull) {
	return "";
}
