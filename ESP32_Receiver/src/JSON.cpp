#include <JSON.h>
#include <ArduinoJson.h>
#include <Serial.h>
#include <MQTTBroker.h>

char data1[2];
char data2[2];

void createJSONpacket(PubSubClient& brokerObj, uint8_t packetNumber)
{
    DynamicJsonDocument doc(12288);

    static uint8_t canOpenCount = 0;

    if (packetNumber == 1)
    {
        // data1[0] = String(packet1.packetType);
        // data1[1] = '\0';
        // doc["PacketType"] = (char *)&packet1.packetType; //?

        
        doc["PacketType"] = (int8_t)packet1.packetType;
        doc["BatterySerialNo"] = packet1.batterySerialNo;
        doc["BatteryID"] = packet1.batteryID;
        doc["BatteryType"] = packet1.batteryType;
        doc["BatteryStatus"] = (int8_t)packet1.batteryStatus;
        doc["ChargerStatus"] = (int8_t)packet1.chargerStatus;

        JsonArray Voltage = doc.createNestedArray("Voltage");
        Voltage.add(packet1.minVolt);
        Voltage.add(packet1.maxVolt);
        Voltage.add(packet1.packVolt);
        Voltage.add(packet1.packMeasureVolt);
        Voltage.add(packet1.measuredSOC);

        JsonArray Temp = doc.createNestedArray("Temp");
        Temp.add(packet1.minTemp);
        Temp.add(packet1.maxTemp);
        doc["BatteryCurrent"] = packet1.batteryCurrent;
        doc["BatterySOC"] = packet1.batterySOC;
        doc["BatterySOH"] = packet1.batterySOH;

        JsonObject Shunt = doc.createNestedObject("Shunt");
        Shunt["I"] = packet1.currentShunt;
        Shunt["SOC"] = packet1.socShunt;
        doc["ErrorMsg"] = packet1.error;
        doc["ErrorMsg2"] = packet1.error2;

        // to do: balancing error, cells, packs

        JsonObject Rec = doc.createNestedObject("Rec");

        JsonObject Rec_Pow = Rec.createNestedObject("Pow");
        Rec_Pow["I"] = packet1.rectifierPowerIn;
        Rec_Pow["O"] = packet1.rectifierPowerOut;

        JsonObject Rec_Current = Rec.createNestedObject("Current");
        Rec_Current["I"] = packet1.rectifierCurrentIn;
        Rec_Current["O"] = packet1.rectifierCurrentOut;

        JsonObject Rec_Volt = Rec.createNestedObject("Volt");
        Rec_Volt["A"] = packet1.rectifierVoltagePhA;
        Rec_Volt["B"] = packet1.rectifierVoltagePhB;
        Rec_Volt["C"] = packet1.rectifierVoltagePhC;
        Rec_Volt["O"] = packet1.rectifierVoltageOut;
        Rec["Temp"] = packet1.rectifierAmbientTemeperature;
        Rec["R_Err1"] = (int8_t)packet1.rectifierError1;
        Rec["R_Err2"] = (int8_t)packet1.rectifierError2;

        JsonObject Inv = doc.createNestedObject("Inv");
        Inv["Curr"] = packet1.inverterCurrent;
        Inv["Volt"] = packet1.inverterVoltage;
        Inv["Err"] = packet1.inverterError;
        Inv["T_amb"] = packet1.inverterTempAmbient;
        Inv["T_HS"] = packet1.inverterTempHeatSink;

        JsonObject AH_data = doc.createNestedObject("AH_data");
        AH_data["Cycle"] = packet1.bCycle;
        AH_data["AHpartial"] = packet1.partialDischargeAH;

        JsonObject ResErr = doc.createNestedObject("ResErr");
        ResErr["MB1"] = packet1.restoredErrorBMS1;
        ResErr["MB2"] = packet1.restoredErrorBMS2;
        ResErr["IER"] = packet1.restoredErrorInverter;
        ResErr["RE1"] = packet1.restoredErrorRectifier1;
        ResErr["RE2"] = packet1.restoredErrorRectifier2;
        ResErr["I_Err"] = packet1.lastDCCurrentErrorValue;
        doc["CanOpenResetCount"] = canOpenCount++;
    }

    else if (packetNumber == 2)
    {
        doc["PacketType"] = (int8_t)packet2.packetType;
        doc["BatterySerialNo"] = packet2.batterySerialNo;
        doc["BatteryID"] = packet2.batteryID;

        JsonArray slaves = doc.createNestedArray("slaves");        

        // Slave 0 cells 1 to 4
        JsonObject slaves_0 = slaves.createNestedObject();
        slaves_0["SID"] = (int8_t)packet2.slaves[0].slaveID;
        slaves_0["SCT"] = packet2.slaves[0].slaveCPUTemp;
        JsonArray slaves_0_cells = slaves_0.createNestedArray("cells");
        JsonObject slaves_0_cells_0 = slaves_0_cells.createNestedObject();
        slaves_0_cells_0["C"] = (int8_t)packet2.slaves[0].cells[0].cellID;
        slaves_0_cells_0["v"] = packet2.slaves[0].cells[0].cellVoltage;
        slaves_0_cells_0["t"] = packet2.slaves[0].cells[0].cellTemp;
        slaves_0_cells_0["S"] = packet2.slaves[0].cells[0].cellSOC;
        JsonObject slaves_0_cells_1 = slaves_0_cells.createNestedObject();
        slaves_0_cells_1["C"] = (int8_t)packet2.slaves[0].cells[1].cellID;
        slaves_0_cells_1["v"] = packet2.slaves[0].cells[1].cellVoltage;
        slaves_0_cells_1["t"] = packet2.slaves[0].cells[1].cellTemp;
        slaves_0_cells_1["S"] = packet2.slaves[0].cells[1].cellSOC;
        JsonObject slaves_0_cells_2 = slaves_0_cells.createNestedObject();
        slaves_0_cells_2["C"] = (int8_t)packet2.slaves[0].cells[2].cellID;
        slaves_0_cells_2["v"] = packet2.slaves[0].cells[2].cellVoltage;
        slaves_0_cells_2["t"] = packet2.slaves[0].cells[2].cellTemp;
        slaves_0_cells_2["S"] = packet2.slaves[0].cells[2].cellSOC;
        JsonObject slaves_0_cells_3 = slaves_0_cells.createNestedObject();
        slaves_0_cells_3["C"] = (int8_t)packet2.slaves[0].cells[3].cellID;
        slaves_0_cells_3["v"] = packet2.slaves[0].cells[3].cellVoltage;
        slaves_0_cells_3["t"] = packet2.slaves[0].cells[3].cellTemp;
        slaves_0_cells_3["S"] = packet2.slaves[0].cells[3].cellSOC;

        /*JsonObject slaves_1 = slaves.createNestedObject();
        slaves_1["SID"] = 2;
        slaves_1["SCT"] = 43;

        JsonArray slaves_1_cells = slaves_1.createNestedArray("cells");

        JsonObject slaves_1_cells_0 = slaves_1_cells.createNestedObject();
        slaves_1_cells_0["C"] = 1;
        slaves_1_cells_0["v"] = 3446;
        slaves_1_cells_0["t"] = 27;
        slaves_1_cells_0["S"] = -33;

        JsonObject slaves_1_cells_1 = slaves_1_cells.createNestedObject();
        slaves_1_cells_1["C"] = 2;
        slaves_1_cells_1["v"] = 3442;
        slaves_1_cells_1["t"] = 27;
        slaves_1_cells_1["S"] = 130;

        JsonObject slaves_1_cells_2 = slaves_1_cells.createNestedObject();
        slaves_1_cells_2["C"] = 3;
        slaves_1_cells_2["v"] = 3442;
        slaves_1_cells_2["t"] = 27;
        slaves_1_cells_2["S"] = 171;

        JsonObject slaves_1_cells_3 = slaves_1_cells.createNestedObject();
        slaves_1_cells_3["C"] = 4;
        slaves_1_cells_3["v"] = 3463;
        slaves_1_cells_3["t"] = 28;
        slaves_1_cells_3["S"] = -14;

        JsonObject slaves_2 = slaves.createNestedObject();
        slaves_2["SID"] = 3;
        slaves_2["SCT"] = 42;

        JsonArray slaves_2_cells = slaves_2.createNestedArray("cells");

        JsonObject slaves_2_cells_0 = slaves_2_cells.createNestedObject();
        slaves_2_cells_0["C"] = 1;
        slaves_2_cells_0["v"] = 3439;
        slaves_2_cells_0["t"] = 27;
        slaves_2_cells_0["S"] = -28;

        JsonObject slaves_2_cells_1 = slaves_2_cells.createNestedObject();
        slaves_2_cells_1["C"] = 2;
        slaves_2_cells_1["v"] = 3436;
        slaves_2_cells_1["t"] = 28;
        slaves_2_cells_1["S"] = -15;

        JsonObject slaves_2_cells_2 = slaves_2_cells.createNestedObject();
        slaves_2_cells_2["C"] = 3;
        slaves_2_cells_2["v"] = 3431;
        slaves_2_cells_2["t"] = 28;
        slaves_2_cells_2["S"] = 924;

        JsonObject slaves_2_cells_3 = slaves_2_cells.createNestedObject();
        slaves_2_cells_3["C"] = 4;
        slaves_2_cells_3["v"] = 3490;
        slaves_2_cells_3["t"] = 27;
        slaves_2_cells_3["S"] = -32;

        JsonObject slaves_3 = slaves.createNestedObject();
        slaves_3["SID"] = 4;
        slaves_3["SCT"] = 41;

        JsonArray slaves_3_cells = slaves_3.createNestedArray("cells");

        JsonObject slaves_3_cells_0 = slaves_3_cells.createNestedObject();
        slaves_3_cells_0["C"] = 1;
        slaves_3_cells_0["v"] = 3426;
        slaves_3_cells_0["t"] = 27;
        slaves_3_cells_0["S"] = -19;

        JsonObject slaves_3_cells_1 = slaves_3_cells.createNestedObject();
        slaves_3_cells_1["C"] = 2;
        slaves_3_cells_1["v"] = 3305;
        slaves_3_cells_1["t"] = 27;
        slaves_3_cells_1["S"] = 164;

        JsonObject slaves_3_cells_2 = slaves_3_cells.createNestedObject();
        slaves_3_cells_2["C"] = 3;
        slaves_3_cells_2["v"] = 3285;
        slaves_3_cells_2["t"] = 27;
        slaves_3_cells_2["S"] = -16;

        JsonObject slaves_3_cells_3 = slaves_3_cells.createNestedObject();
        slaves_3_cells_3["C"] = 4;
        slaves_3_cells_3["v"] = 3294;
        slaves_3_cells_3["t"] = 27;
        slaves_3_cells_3["S"] = 240;

        JsonObject slaves_4 = slaves.createNestedObject();
        slaves_4["SID"] = 5;
        slaves_4["SCT"] = 42;

        JsonArray slaves_4_cells = slaves_4.createNestedArray("cells");

        JsonObject slaves_4_cells_0 = slaves_4_cells.createNestedObject();
        slaves_4_cells_0["C"] = 1;
        slaves_4_cells_0["v"] = 3392;
        slaves_4_cells_0["t"] = 28;
        slaves_4_cells_0["S"] = -99;

        JsonObject slaves_4_cells_1 = slaves_4_cells.createNestedObject();
        slaves_4_cells_1["C"] = 2;
        slaves_4_cells_1["v"] = 3426;
        slaves_4_cells_1["t"] = 27;
        slaves_4_cells_1["S"] = -31;

        JsonObject slaves_4_cells_2 = slaves_4_cells.createNestedObject();
        slaves_4_cells_2["C"] = 3;
        slaves_4_cells_2["v"] = 3439;
        slaves_4_cells_2["t"] = 28;
        slaves_4_cells_2["S"] = 274;

        JsonObject slaves_4_cells_3 = slaves_4_cells.createNestedObject();
        slaves_4_cells_3["C"] = 4;
        slaves_4_cells_3["v"] = 3489;
        slaves_4_cells_3["t"] = 27;
        slaves_4_cells_3["S"] = 136;

        JsonObject slaves_5 = slaves.createNestedObject();
        slaves_5["SID"] = 6;
        slaves_5["SCT"] = 43;

        JsonArray slaves_5_cells = slaves_5.createNestedArray("cells");

        JsonObject slaves_5_cells_0 = slaves_5_cells.createNestedObject();
        slaves_5_cells_0["C"] = 1;
        slaves_5_cells_0["v"] = 3426;
        slaves_5_cells_0["t"] = 28;
        slaves_5_cells_0["S"] = 901;

        JsonObject slaves_5_cells_1 = slaves_5_cells.createNestedObject();
        slaves_5_cells_1["C"] = 2;
        slaves_5_cells_1["v"] = 3447;
        slaves_5_cells_1["t"] = 28;
        slaves_5_cells_1["S"] = 211;

        JsonObject slaves_5_cells_2 = slaves_5_cells.createNestedObject();
        slaves_5_cells_2["C"] = 3;
        slaves_5_cells_2["v"] = 3445;
        slaves_5_cells_2["t"] = 28;
        slaves_5_cells_2["S"] = 259;

        JsonObject slaves_5_cells_3 = slaves_5_cells.createNestedObject();
        slaves_5_cells_3["C"] = 4;
        slaves_5_cells_3["v"] = 3459;
        slaves_5_cells_3["t"] = 27;
        slaves_5_cells_3["S"] = 286;

        JsonObject slaves_6 = slaves.createNestedObject();
        slaves_6["SID"] = 7;
        slaves_6["SCT"] = 44;

        JsonArray slaves_6_cells = slaves_6.createNestedArray("cells");

        JsonObject slaves_6_cells_0 = slaves_6_cells.createNestedObject();
        slaves_6_cells_0["C"] = 1;
        slaves_6_cells_0["v"] = 3446;
        slaves_6_cells_0["t"] = 27;
        slaves_6_cells_0["S"] = 287;

        JsonObject slaves_6_cells_1 = slaves_6_cells.createNestedObject();
        slaves_6_cells_1["C"] = 2;
        slaves_6_cells_1["v"] = 3430;
        slaves_6_cells_1["t"] = 27;
        slaves_6_cells_1["S"] = -52;

        JsonObject slaves_6_cells_2 = slaves_6_cells.createNestedObject();
        slaves_6_cells_2["C"] = 3;
        slaves_6_cells_2["v"] = 3445;
        slaves_6_cells_2["t"] = 27;
        slaves_6_cells_2["S"] = 317;

        JsonObject slaves_6_cells_3 = slaves_6_cells.createNestedObject();
        slaves_6_cells_3["C"] = 4;
        slaves_6_cells_3["v"] = 3469;
        slaves_6_cells_3["t"] = 27;
        slaves_6_cells_3["S"] = 261;

        JsonObject slaves_7 = slaves.createNestedObject();
        slaves_7["SID"] = 8;
        slaves_7["SCT"] = 43;

        JsonArray slaves_7_cells = slaves_7.createNestedArray("cells");

        JsonObject slaves_7_cells_0 = slaves_7_cells.createNestedObject();
        slaves_7_cells_0["C"] = 1;
        slaves_7_cells_0["v"] = 3442;
        slaves_7_cells_0["t"] = 28;
        slaves_7_cells_0["S"] = 146;

        JsonObject slaves_7_cells_1 = slaves_7_cells.createNestedObject();
        slaves_7_cells_1["C"] = 2;
        slaves_7_cells_1["v"] = 3435;
        slaves_7_cells_1["t"] = 28;
        slaves_7_cells_1["S"] = 528;

        JsonObject slaves_7_cells_2 = slaves_7_cells.createNestedObject();
        slaves_7_cells_2["C"] = 3;
        slaves_7_cells_2["v"] = 3446;
        slaves_7_cells_2["t"] = 28;
        slaves_7_cells_2["S"] = -42;

        JsonObject slaves_7_cells_3 = slaves_7_cells.createNestedObject();
        slaves_7_cells_3["C"] = 4;
        slaves_7_cells_3["v"] = 3485;
        slaves_7_cells_3["t"] = 27;
        slaves_7_cells_3["S"] = -17;

        JsonObject slaves_8 = slaves.createNestedObject();
        slaves_8["SID"] = 9;
        slaves_8["SCT"] = 42;

        JsonArray slaves_8_cells = slaves_8.createNestedArray("cells");

        JsonObject slaves_8_cells_0 = slaves_8_cells.createNestedObject();
        slaves_8_cells_0["C"] = 1;
        slaves_8_cells_0["v"] = 3430;
        slaves_8_cells_0["t"] = 27;
        slaves_8_cells_0["S"] = -60;

        JsonObject slaves_8_cells_1 = slaves_8_cells.createNestedObject();
        slaves_8_cells_1["C"] = 2;
        slaves_8_cells_1["v"] = 3447;
        slaves_8_cells_1["t"] = 28;
        slaves_8_cells_1["S"] = -25;

        JsonObject slaves_8_cells_2 = slaves_8_cells.createNestedObject();
        slaves_8_cells_2["C"] = 3;
        slaves_8_cells_2["v"] = 3442;
        slaves_8_cells_2["t"] = 27;
        slaves_8_cells_2["S"] = 299;

        JsonObject slaves_8_cells_3 = slaves_8_cells.createNestedObject();
        slaves_8_cells_3["C"] = 4;
        slaves_8_cells_3["v"] = 3474;
        slaves_8_cells_3["t"] = 27;
        slaves_8_cells_3["S"] = 131;

        JsonObject slaves_9 = slaves.createNestedObject();
        slaves_9["SID"] = 10;
        slaves_9["SCT"] = 42;

        JsonArray slaves_9_cells = slaves_9.createNestedArray("cells");

        JsonObject slaves_9_cells_0 = slaves_9_cells.createNestedObject();
        slaves_9_cells_0["C"] = 1;
        slaves_9_cells_0["v"] = 3436;
        slaves_9_cells_0["t"] = 27;
        slaves_9_cells_0["S"] = 245;

        JsonObject slaves_9_cells_1 = slaves_9_cells.createNestedObject();
        slaves_9_cells_1["C"] = 2;
        slaves_9_cells_1["v"] = 3442;
        slaves_9_cells_1["t"] = 27;
        slaves_9_cells_1["S"] = 115;

        JsonObject slaves_9_cells_2 = slaves_9_cells.createNestedObject();
        slaves_9_cells_2["C"] = 3;
        slaves_9_cells_2["v"] = 3443;
        slaves_9_cells_2["t"] = 27;
        slaves_9_cells_2["S"] = -37;

        JsonObject slaves_9_cells_3 = slaves_9_cells.createNestedObject();
        slaves_9_cells_3["C"] = 4;
        slaves_9_cells_3["v"] = 3527;
        slaves_9_cells_3["t"] = 27;
        slaves_9_cells_3["S"] = 194;

        JsonObject slaves_10 = slaves.createNestedObject();
        slaves_10["SID"] = 11;
        slaves_10["SCT"] = 42;

        JsonArray slaves_10_cells = slaves_10.createNestedArray("cells");

        JsonObject slaves_10_cells_0 = slaves_10_cells.createNestedObject();
        slaves_10_cells_0["C"] = 1;
        slaves_10_cells_0["v"] = 3444;
        slaves_10_cells_0["t"] = 27;
        slaves_10_cells_0["S"] = -13;

        JsonObject slaves_10_cells_1 = slaves_10_cells.createNestedObject();
        slaves_10_cells_1["C"] = 2;
        slaves_10_cells_1["v"] = 3437;
        slaves_10_cells_1["t"] = 27;
        slaves_10_cells_1["S"] = 265;

        JsonObject slaves_10_cells_2 = slaves_10_cells.createNestedObject();
        slaves_10_cells_2["C"] = 3;
        slaves_10_cells_2["v"] = 3436;
        slaves_10_cells_2["t"] = 27;
        slaves_10_cells_2["S"] = 194;

        JsonObject slaves_10_cells_3 = slaves_10_cells.createNestedObject();
        slaves_10_cells_3["C"] = 4;
        slaves_10_cells_3["v"] = 3503;
        slaves_10_cells_3["t"] = 27;
        slaves_10_cells_3["S"] = -16;

        JsonObject slaves_11 = slaves.createNestedObject();
        slaves_11["SID"] = 12;
        slaves_11["SCT"] = 41;

        JsonArray slaves_11_cells = slaves_11.createNestedArray("cells");

        JsonObject slaves_11_cells_0 = slaves_11_cells.createNestedObject();
        slaves_11_cells_0["C"] = 1;
        slaves_11_cells_0["v"] = 3428;
        slaves_11_cells_0["t"] = 27;
        slaves_11_cells_0["S"] = -51;

        JsonObject slaves_11_cells_1 = slaves_11_cells.createNestedObject();
        slaves_11_cells_1["C"] = 2;
        slaves_11_cells_1["v"] = 3424;
        slaves_11_cells_1["t"] = 27;
        slaves_11_cells_1["S"] = 155;

        JsonObject slaves_11_cells_2 = slaves_11_cells.createNestedObject();
        slaves_11_cells_2["C"] = 3;
        slaves_11_cells_2["v"] = 3428;
        slaves_11_cells_2["t"] = 27;
        slaves_11_cells_2["S"] = -86;

        JsonObject slaves_11_cells_3 = slaves_11_cells.createNestedObject();
        slaves_11_cells_3["C"] = 4;
        slaves_11_cells_3["v"] = 3576;
        slaves_11_cells_3["t"] = 26;
        slaves_11_cells_3["S"] = 163;

        JsonObject slaves_12 = slaves.createNestedObject();
        slaves_12["SID"] = 13;
        slaves_12["SCT"] = 41;

        JsonArray slaves_12_cells = slaves_12.createNestedArray("cells");

        JsonObject slaves_12_cells_0 = slaves_12_cells.createNestedObject();
        slaves_12_cells_0["C"] = 1;
        slaves_12_cells_0["v"] = 3424;
        slaves_12_cells_0["t"] = 27;
        slaves_12_cells_0["S"] = -27;

        JsonObject slaves_12_cells_1 = slaves_12_cells.createNestedObject();
        slaves_12_cells_1["C"] = 2;
        slaves_12_cells_1["v"] = 3426;
        slaves_12_cells_1["t"] = 27;
        slaves_12_cells_1["S"] = -31;

        JsonObject slaves_12_cells_2 = slaves_12_cells.createNestedObject();
        slaves_12_cells_2["C"] = 3;
        slaves_12_cells_2["v"] = 3444;
        slaves_12_cells_2["t"] = 27;
        slaves_12_cells_2["S"] = -12;

        JsonObject slaves_12_cells_3 = slaves_12_cells.createNestedObject();
        slaves_12_cells_3["C"] = 4;
        slaves_12_cells_3["v"] = 3473;
        slaves_12_cells_3["t"] = 27;
        slaves_12_cells_3["S"] = 275;

        JsonObject slaves_13 = slaves.createNestedObject();
        slaves_13["SID"] = 14;
        slaves_13["SCT"] = 42;

        JsonArray slaves_13_cells = slaves_13.createNestedArray("cells");

        JsonObject slaves_13_cells_0 = slaves_13_cells.createNestedObject();
        slaves_13_cells_0["C"] = 1;
        slaves_13_cells_0["v"] = 3435;
        slaves_13_cells_0["t"] = 27;
        slaves_13_cells_0["S"] = -77;

        JsonObject slaves_13_cells_1 = slaves_13_cells.createNestedObject();
        slaves_13_cells_1["C"] = 2;
        slaves_13_cells_1["v"] = 3447;
        slaves_13_cells_1["t"] = 27;
        slaves_13_cells_1["S"] = -18;

        JsonObject slaves_13_cells_2 = slaves_13_cells.createNestedObject();
        slaves_13_cells_2["C"] = 3;
        slaves_13_cells_2["v"] = 3441;
        slaves_13_cells_2["t"] = 27;
        slaves_13_cells_2["S"] = 545;

        JsonObject slaves_13_cells_3 = slaves_13_cells.createNestedObject();
        slaves_13_cells_3["C"] = 4;
        slaves_13_cells_3["v"] = 3508;
        slaves_13_cells_3["t"] = 27;
        slaves_13_cells_3["S"] = 106;

        JsonObject slaves_14 = slaves.createNestedObject();
        slaves_14["SID"] = 15;
        slaves_14["SCT"] = 40;

        JsonArray slaves_14_cells = slaves_14.createNestedArray("cells");

        JsonObject slaves_14_cells_0 = slaves_14_cells.createNestedObject();
        slaves_14_cells_0["C"] = 1;
        slaves_14_cells_0["v"] = 3447;
        slaves_14_cells_0["t"] = 27;
        slaves_14_cells_0["S"] = 749;

        JsonObject slaves_14_cells_1 = slaves_14_cells.createNestedObject();
        slaves_14_cells_1["C"] = 2;
        slaves_14_cells_1["v"] = 3432;
        slaves_14_cells_1["t"] = 27;
        slaves_14_cells_1["S"] = 317;

        JsonObject slaves_14_cells_2 = slaves_14_cells.createNestedObject();
        slaves_14_cells_2["C"] = 3;
        slaves_14_cells_2["v"] = 3449;
        slaves_14_cells_2["t"] = 27;
        slaves_14_cells_2["S"] = -28;

        JsonObject slaves_14_cells_3 = slaves_14_cells.createNestedObject();
        slaves_14_cells_3["C"] = 4;
        slaves_14_cells_3["v"] = 3577;
        slaves_14_cells_3["t"] = 27;
        slaves_14_cells_3["S"] = -19;

        JsonObject slaves_15 = slaves.createNestedObject();
        slaves_15["SID"] = 16;
        slaves_15["SCT"] = 40;

        JsonArray slaves_15_cells = slaves_15.createNestedArray("cells");

        JsonObject slaves_15_cells_0 = slaves_15_cells.createNestedObject();
        slaves_15_cells_0["C"] = 1;
        slaves_15_cells_0["v"] = 3445;
        slaves_15_cells_0["t"] = 27;
        slaves_15_cells_0["S"] = -31;

        JsonObject slaves_15_cells_1 = slaves_15_cells.createNestedObject();
        slaves_15_cells_1["C"] = 2;
        slaves_15_cells_1["v"] = 3443;
        slaves_15_cells_1["t"] = 27;
        slaves_15_cells_1["S"] = -32;

        JsonObject slaves_15_cells_2 = slaves_15_cells.createNestedObject();
        slaves_15_cells_2["C"] = 3;
        slaves_15_cells_2["v"] = 3439;
        slaves_15_cells_2["t"] = 27;
        slaves_15_cells_2["S"] = 232;

        JsonObject slaves_15_cells_3 = slaves_15_cells.createNestedObject();
        slaves_15_cells_3["C"] = 4;
        slaves_15_cells_3["v"] = 3461;
        slaves_15_cells_3["t"] = 27;
        slaves_15_cells_3["S"] = -20;

        JsonObject slaves_16 = slaves.createNestedObject();
        slaves_16["SID"] = 17;
        slaves_16["SCT"] = 43;

        JsonArray slaves_16_cells = slaves_16.createNestedArray("cells");

        JsonObject slaves_16_cells_0 = slaves_16_cells.createNestedObject();
        slaves_16_cells_0["C"] = 1;
        slaves_16_cells_0["v"] = 3438;
        slaves_16_cells_0["t"] = 27;
        slaves_16_cells_0["S"] = 269;

        JsonObject slaves_16_cells_1 = slaves_16_cells.createNestedObject();
        slaves_16_cells_1["C"] = 2;
        slaves_16_cells_1["v"] = 3444;
        slaves_16_cells_1["t"] = 27;
        slaves_16_cells_1["S"] = -10;

        JsonObject slaves_16_cells_2 = slaves_16_cells.createNestedObject();
        slaves_16_cells_2["C"] = 3;
        slaves_16_cells_2["v"] = 3440;
        slaves_16_cells_2["t"] = 27;
        slaves_16_cells_2["S"] = -20;

        JsonObject slaves_16_cells_3 = slaves_16_cells.createNestedObject();
        slaves_16_cells_3["C"] = 4;
        slaves_16_cells_3["v"] = 3505;
        slaves_16_cells_3["t"] = 27;
        slaves_16_cells_3["S"] = -24;

        JsonObject slaves_17 = slaves.createNestedObject();
        slaves_17["SID"] = 18;
        slaves_17["SCT"] = 40;

        JsonArray slaves_17_cells = slaves_17.createNestedArray("cells");

        JsonObject slaves_17_cells_0 = slaves_17_cells.createNestedObject();
        slaves_17_cells_0["C"] = 1;
        slaves_17_cells_0["v"] = 3429;
        slaves_17_cells_0["t"] = 27;
        slaves_17_cells_0["S"] = -28;

        JsonObject slaves_17_cells_1 = slaves_17_cells.createNestedObject();
        slaves_17_cells_1["C"] = 2;
        slaves_17_cells_1["v"] = 3425;
        slaves_17_cells_1["t"] = 27;
        slaves_17_cells_1["S"] = -45;

        JsonObject slaves_17_cells_2 = slaves_17_cells.createNestedObject();
        slaves_17_cells_2["C"] = 3;
        slaves_17_cells_2["v"] = 3436;
        slaves_17_cells_2["t"] = 27;
        slaves_17_cells_2["S"] = 223;

        JsonObject slaves_17_cells_3 = slaves_17_cells.createNestedObject();
        slaves_17_cells_3["C"] = 4;
        slaves_17_cells_3["v"] = 3463;
        slaves_17_cells_3["t"] = 27;
        slaves_17_cells_3["S"] = 668;

        JsonObject slaves_18 = slaves.createNestedObject();
        slaves_18["SID"] = 19;
        slaves_18["SCT"] = 38;

        JsonArray slaves_18_cells = slaves_18.createNestedArray("cells");

        JsonObject slaves_18_cells_0 = slaves_18_cells.createNestedObject();
        slaves_18_cells_0["C"] = 1;
        slaves_18_cells_0["v"] = 3431;
        slaves_18_cells_0["t"] = 26;
        slaves_18_cells_0["S"] = -24;

        JsonObject slaves_18_cells_1 = slaves_18_cells.createNestedObject();
        slaves_18_cells_1["C"] = 2;
        slaves_18_cells_1["v"] = 3426;
        slaves_18_cells_1["t"] = 26;
        slaves_18_cells_1["S"] = 222;

        JsonObject slaves_18_cells_2 = slaves_18_cells.createNestedObject();
        slaves_18_cells_2["C"] = 3;
        slaves_18_cells_2["v"] = 3433;
        slaves_18_cells_2["t"] = 26;
        slaves_18_cells_2["S"] = -36;

        JsonObject slaves_18_cells_3 = slaves_18_cells.createNestedObject();
        slaves_18_cells_3["C"] = 4;
        slaves_18_cells_3["v"] = 3559;
        slaves_18_cells_3["t"] = 26;
        slaves_18_cells_3["S"] = 164;

        JsonObject slaves_19 = slaves.createNestedObject();
        slaves_19["SID"] = 20;
        slaves_19["SCT"] = 39;

        JsonArray slaves_19_cells = slaves_19.createNestedArray("cells");

        JsonObject slaves_19_cells_0 = slaves_19_cells.createNestedObject();
        slaves_19_cells_0["C"] = 1;
        slaves_19_cells_0["v"] = 3432;
        slaves_19_cells_0["t"] = 26;
        slaves_19_cells_0["S"] = 190;

        JsonObject slaves_19_cells_1 = slaves_19_cells.createNestedObject();
        slaves_19_cells_1["C"] = 2;
        slaves_19_cells_1["v"] = 3438;
        slaves_19_cells_1["t"] = 26;
        slaves_19_cells_1["S"] = -25;

        JsonObject slaves_19_cells_2 = slaves_19_cells.createNestedObject();
        slaves_19_cells_2["C"] = 3;
        slaves_19_cells_2["v"] = 3439;
        slaves_19_cells_2["t"] = 26;
        slaves_19_cells_2["S"] = 115;

        JsonObject slaves_19_cells_3 = slaves_19_cells.createNestedObject();
        slaves_19_cells_3["C"] = 4;
        slaves_19_cells_3["v"] = 3561;
        slaves_19_cells_3["t"] = 26;
        slaves_19_cells_3["S"] = -11;

        JsonObject slaves_20 = slaves.createNestedObject();
        slaves_20["SID"] = 21;
        slaves_20["SCT"] = 42;

        JsonArray slaves_20_cells = slaves_20.createNestedArray("cells");

        JsonObject slaves_20_cells_0 = slaves_20_cells.createNestedObject();
        slaves_20_cells_0["C"] = 1;
        slaves_20_cells_0["v"] = 3424;
        slaves_20_cells_0["t"] = 26;
        slaves_20_cells_0["S"] = -22;

        JsonObject slaves_20_cells_1 = slaves_20_cells.createNestedObject();
        slaves_20_cells_1["C"] = 2;
        slaves_20_cells_1["v"] = 3447;
        slaves_20_cells_1["t"] = 26;
        slaves_20_cells_1["S"] = 170;

        JsonObject slaves_20_cells_2 = slaves_20_cells.createNestedObject();
        slaves_20_cells_2["C"] = 3;
        slaves_20_cells_2["v"] = 3441;
        slaves_20_cells_2["t"] = 26;
        slaves_20_cells_2["S"] = -18;

        JsonObject slaves_20_cells_3 = slaves_20_cells.createNestedObject();
        slaves_20_cells_3["C"] = 4;
        slaves_20_cells_3["v"] = 3469;
        slaves_20_cells_3["t"] = 25;
        slaves_20_cells_3["S"] = -25;

        JsonObject slaves_21 = slaves.createNestedObject();
        slaves_21["SID"] = 22;
        slaves_21["SCT"] = 40;

        JsonArray slaves_21_cells = slaves_21.createNestedArray("cells");

        JsonObject slaves_21_cells_0 = slaves_21_cells.createNestedObject();
        slaves_21_cells_0["C"] = 1;
        slaves_21_cells_0["v"] = 3434;
        slaves_21_cells_0["t"] = 26;
        slaves_21_cells_0["S"] = -87;

        JsonObject slaves_21_cells_1 = slaves_21_cells.createNestedObject();
        slaves_21_cells_1["C"] = 2;
        slaves_21_cells_1["v"] = 3439;
        slaves_21_cells_1["t"] = 26;
        slaves_21_cells_1["S"] = 143;

        JsonObject slaves_21_cells_2 = slaves_21_cells.createNestedObject();
        slaves_21_cells_2["C"] = 3;
        slaves_21_cells_2["v"] = 3435;
        slaves_21_cells_2["t"] = 27;
        slaves_21_cells_2["S"] = -59;

        JsonObject slaves_21_cells_3 = slaves_21_cells.createNestedObject();
        slaves_21_cells_3["C"] = 4;
        slaves_21_cells_3["v"] = 3461;
        slaves_21_cells_3["t"] = 26;
        slaves_21_cells_3["S"] = 878;

        JsonObject slaves_22 = slaves.createNestedObject();
        slaves_22["SID"] = 23;
        slaves_22["SCT"] = 41;

        JsonArray slaves_22_cells = slaves_22.createNestedArray("cells");

        JsonObject slaves_22_cells_0 = slaves_22_cells.createNestedObject();
        slaves_22_cells_0["C"] = 1;
        slaves_22_cells_0["v"] = 3423;
        slaves_22_cells_0["t"] = 27;
        slaves_22_cells_0["S"] = 223;

        JsonObject slaves_22_cells_1 = slaves_22_cells.createNestedObject();
        slaves_22_cells_1["C"] = 2;
        slaves_22_cells_1["v"] = 3443;
        slaves_22_cells_1["t"] = 27;
        slaves_22_cells_1["S"] = -25;

        JsonObject slaves_22_cells_2 = slaves_22_cells.createNestedObject();
        slaves_22_cells_2["C"] = 3;
        slaves_22_cells_2["v"] = 3427;
        slaves_22_cells_2["t"] = 27;
        slaves_22_cells_2["S"] = -11;

        JsonObject slaves_22_cells_3 = slaves_22_cells.createNestedObject();
        slaves_22_cells_3["C"] = 4;
        slaves_22_cells_3["v"] = 3466;
        slaves_22_cells_3["t"] = 26;
        slaves_22_cells_3["S"] = -11;

        JsonObject slaves_23 = slaves.createNestedObject();
        slaves_23["SID"] = 24;
        slaves_23["SCT"] = 42;

        JsonArray slaves_23_cells = slaves_23.createNestedArray("cells");

        JsonObject slaves_23_cells_0 = slaves_23_cells.createNestedObject();
        slaves_23_cells_0["C"] = 1;
        slaves_23_cells_0["v"] = 3441;
        slaves_23_cells_0["t"] = 27;
        slaves_23_cells_0["S"] = -22;

        JsonObject slaves_23_cells_1 = slaves_23_cells.createNestedObject();
        slaves_23_cells_1["C"] = 2;
        slaves_23_cells_1["v"] = 3441;
        slaves_23_cells_1["t"] = 26;
        slaves_23_cells_1["S"] = -25;

        JsonObject slaves_23_cells_2 = slaves_23_cells.createNestedObject();
        slaves_23_cells_2["C"] = 3;
        slaves_23_cells_2["v"] = 3430;
        slaves_23_cells_2["t"] = 27;
        slaves_23_cells_2["S"] = -26;

        JsonObject slaves_23_cells_3 = slaves_23_cells.createNestedObject();
        slaves_23_cells_3["C"] = 4;
        slaves_23_cells_3["v"] = 3490;
        slaves_23_cells_3["t"] = 26;
        slaves_23_cells_3["S"] = 740;

        JsonObject slaves_24 = slaves.createNestedObject();
        slaves_24["SID"] = 25;
        slaves_24["SCT"] = 41;

        JsonArray slaves_24_cells = slaves_24.createNestedArray("cells");

        JsonObject slaves_24_cells_0 = slaves_24_cells.createNestedObject();
        slaves_24_cells_0["C"] = 1;
        slaves_24_cells_0["v"] = 3419;
        slaves_24_cells_0["t"] = 26;
        slaves_24_cells_0["S"] = -10;

        JsonObject slaves_24_cells_1 = slaves_24_cells.createNestedObject();
        slaves_24_cells_1["C"] = 2;
        slaves_24_cells_1["v"] = 3426;
        slaves_24_cells_1["t"] = 26;
        slaves_24_cells_1["S"] = -24;

        JsonObject slaves_24_cells_2 = slaves_24_cells.createNestedObject();
        slaves_24_cells_2["C"] = 3;
        slaves_24_cells_2["v"] = 3445;
        slaves_24_cells_2["t"] = 26;
        slaves_24_cells_2["S"] = -16;

        JsonObject slaves_24_cells_3 = slaves_24_cells.createNestedObject();
        slaves_24_cells_3["C"] = 4;
        slaves_24_cells_3["v"] = 3566;
        slaves_24_cells_3["t"] = 26;
        slaves_24_cells_3["S"] = -55;

        JsonObject slaves_25 = slaves.createNestedObject();
        slaves_25["SID"] = 26;
        slaves_25["SCT"] = 42;

        JsonArray slaves_25_cells = slaves_25.createNestedArray("cells");

        JsonObject slaves_25_cells_0 = slaves_25_cells.createNestedObject();
        slaves_25_cells_0["C"] = 1;
        slaves_25_cells_0["v"] = 3438;
        slaves_25_cells_0["t"] = 27;
        slaves_25_cells_0["S"] = 125;

        JsonObject slaves_25_cells_1 = slaves_25_cells.createNestedObject();
        slaves_25_cells_1["C"] = 2;
        slaves_25_cells_1["v"] = 3439;
        slaves_25_cells_1["t"] = 27;
        slaves_25_cells_1["S"] = -23;

        JsonObject slaves_25_cells_2 = slaves_25_cells.createNestedObject();
        slaves_25_cells_2["C"] = 3;
        slaves_25_cells_2["v"] = 3448;
        slaves_25_cells_2["t"] = 26;
        slaves_25_cells_2["S"] = -28;

        JsonObject slaves_25_cells_3 = slaves_25_cells.createNestedObject();
        slaves_25_cells_3["C"] = 4;
        slaves_25_cells_3["v"] = 3508;
        slaves_25_cells_3["t"] = 23;
        slaves_25_cells_3["S"] = -16;

        JsonObject slaves_26 = slaves.createNestedObject();
        slaves_26["SID"] = 27;
        slaves_26["SCT"] = 40;

        JsonArray slaves_26_cells = slaves_26.createNestedArray("cells");

        JsonObject slaves_26_cells_0 = slaves_26_cells.createNestedObject();
        slaves_26_cells_0["C"] = 1;
        slaves_26_cells_0["v"] = 3438;
        slaves_26_cells_0["t"] = 26;
        slaves_26_cells_0["S"] = -18;

        JsonObject slaves_26_cells_1 = slaves_26_cells.createNestedObject();
        slaves_26_cells_1["C"] = 2;
        slaves_26_cells_1["v"] = 3437;
        slaves_26_cells_1["t"] = 26;
        slaves_26_cells_1["S"] = -26;

        JsonObject slaves_26_cells_2 = slaves_26_cells.createNestedObject();
        slaves_26_cells_2["C"] = 3;
        slaves_26_cells_2["v"] = 3434;
        slaves_26_cells_2["t"] = 26;
        slaves_26_cells_2["S"] = 809;

        JsonObject slaves_26_cells_3 = slaves_26_cells.createNestedObject();
        slaves_26_cells_3["C"] = 4;
        slaves_26_cells_3["v"] = 3463;
        slaves_26_cells_3["t"] = 26;
        slaves_26_cells_3["S"] = -16;*/
    }

    String output;
    size_t payloadSize = serializeJson(doc, output);
    brokerObj.publish(PUBLISH_TOPIC1, String(output).c_str(), payloadSize);
}

