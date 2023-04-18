#pragma once

struct LEANCLOUD_API FLCGeoPoint {
	double Latitude = 0;
	double Longitude = 0;
	FLCGeoPoint() = default;
	FLCGeoPoint(double InLatitude, double InLongitude): Latitude(InLatitude), Longitude(InLongitude){};

	double DistanceInKilometersTo(const FLCGeoPoint& GeoPoint);
	double DistanceInMilesTo(const FLCGeoPoint& GeoPoint);
	double DistanceInRadiansTo(const FLCGeoPoint& GeoPoint);
};
// public static final double earthMeanRadiusInKM = 6378.140;
// static double ONE_KM_TO_MILES = 1.609344;