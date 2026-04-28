#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum Unit {
    KM,
    METERS,
    FEET,
    UNKNOWN
};

double TroposphereTempCalc(double height);
double TropopauseTempCalc();
double StratosphereTempCalc(double relationalHeight);
double TempCalcISA(double height);

Unit GetUnit(const string& header);
double ConvertToKm(double h, Unit unit);
void RunTest(const string& filename, const string& outfile);

#define BASE_TROPOSPHERE_TEMP 15
#define LAPSE_TROPOSPHERE 6.5

#define BASE_TROPOPAUSE_TEMP (-56.5)
#define TROPOPAUSE_START_POINT 11

#define BASE_STRATOSPHERE_TEMP (-56.5)
#define BASE_STRATOSPHERE_HEIGHT 20
#define LAPSE_STRATOSPHERE 1
#define STRATOSPHERE_START_POINT 20

#define FEET_TO_KM 0.0003048
#define METERS_TO_KM 1000.0

#define HEIGHT_UPPER_BOUND_KM 25

int main() {
    RunTest("../Test_1.txt", "../test1.csv");
    RunTest("../Test_2.txt", "../test2.csv");
    RunTest("../Test_3.txt", "../test3.csv");
    return 0;
}

double TempCalcISA(double height) {
    // out of bounds
    if (height < 0 || height > HEIGHT_UPPER_BOUND_KM)
        return NAN;

    if (height <= TROPOPAUSE_START_POINT)
        return TroposphereTempCalc(height);

    if (height <= STRATOSPHERE_START_POINT)
        return TropopauseTempCalc();

    return StratosphereTempCalc(height - BASE_STRATOSPHERE_HEIGHT);
}

double TroposphereTempCalc(double height) {
    // temperature is decreasing in the Troposphere
    return BASE_TROPOSPHERE_TEMP - LAPSE_TROPOSPHERE * height;
}

double TropopauseTempCalc() {
    // temperature is constant in the Tropopause
    return BASE_TROPOPAUSE_TEMP;
}

double StratosphereTempCalc(double relationalHeight) {
    // temperature is increasing in the Stratosphere
    return BASE_STRATOSPHERE_TEMP + LAPSE_STRATOSPHERE * relationalHeight;
}

Unit GetUnit(const string& header) {
    if (header.find("Alt[ft]") != string::npos)
        return FEET;

    if (header.find("Alt[m]") != string::npos)
        return METERS;

    if (header.find("Alt[km]") != string::npos)
        return KM;
    return UNKNOWN;
}

double ConvertToKm(double h, Unit unit) {
    if (unit == UNKNOWN)
        return NAN;
    if (unit == METERS)
        return h / METERS_TO_KM;

    if (unit == FEET)
        return h * FEET_TO_KM;

    return h; // Unit == KM
}

void RunTest(const string& filename, const string& outfile) {
    ifstream file(filename);
    ofstream out(outfile);

    if (!file) {
        cout << "Failed to open file\n";
        return;
    }

    // get the unit and skip the first line
    string header;
    getline(file, header);

    Unit unit = GetUnit(header);

    // if the unit is not recognised the code stops here
    if (unit == UNKNOWN) return;

    out << "height_km,expected,actual,error\n";

    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        // splits row to temp, comma and alt
        double expected, h;
        char comma;

        ss >> expected >> comma >> h;

        double hKM = ConvertToKm(h, unit);
        double result = TempCalcISA(hKM);

        double error = fabs(result - expected);

        out << hKM << "," << expected << "," << result << "," << error << "\n";
    }
}
