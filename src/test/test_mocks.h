TEST(digitalWrite, PUMP_LOW)
{
    pump_state = false;
    digitalWrite(PUMP, LOW);
    ASSERT_EQ(pump_state, true);
}

TEST(digitalWrite, PUMP_HIGH)
{
    pump_state = true;
    digitalWrite(PUMP, HIGH);
    ASSERT_EQ(pump_state, false);
}

TEST(digitalWrite, VALVETOP_LOW)
{
    valve_state_top = false;
    digitalWrite(VALVETOP, LOW);
    ASSERT_EQ(valve_state_top, true);
}

TEST(digitalWrite, VALVETOP_HIGH)
{
    valve_state_top = true;
    digitalWrite(VALVETOP, HIGH);
    ASSERT_EQ(valve_state_top, false);
}

TEST(digitalWrite, VALVEBOTTOM_LOW)
{
    valve_state_bottom = false;
    digitalWrite(VALVEBOTTOM, LOW);
    ASSERT_EQ(valve_state_bottom, true);
}

TEST(digitalWrite, VALVEBOTTOM_HIGH)
{
    valve_state_bottom = true;
    digitalWrite(VALVEBOTTOM, HIGH);
    ASSERT_EQ(valve_state_bottom, false);
}

TEST(digitalWrite, MEASURE_WL_HIGH)
{
    measure_current_wl = true;
    digitalWrite(MEASURE_WL, HIGH);
    ASSERT_EQ(measure_current_wl, false);
}

TEST(digitalWrite, MEASURE_WL_LOW)
{
    measure_current_wl = false;
    digitalWrite(MEASURE_WL, LOW);
    ASSERT_EQ(measure_current_wl, true);
}

TEST(digitalRead, PUMP_LOW)
{
    pump_state = true;
    ASSERT_EQ(digitalRead(PUMP), LOW);
}

TEST(digitalRead, PUMP_HIGH)
{
    pump_state = false;
    ASSERT_EQ(digitalRead(PUMP), HIGH);
}

TEST(digitalRead, VALVETOP_LOW)
{
    valve_state_top = true;
    ASSERT_EQ(digitalRead(VALVETOP), LOW);
}

TEST(digitalRead, VALVETOP_HIGH)
{
    valve_state_top = false;
    ASSERT_EQ(digitalRead(VALVETOP), HIGH);
}

TEST(digitalRead, VALVEBOTTOM_LOW)
{
    valve_state_bottom = true;
    ASSERT_EQ(digitalRead(VALVEBOTTOM), LOW);
}

TEST(digitalRead, VALVEBOTTOM_HIGH)
{
    valve_state_bottom = false;
    ASSERT_EQ(digitalRead(VALVEBOTTOM), HIGH);
}

TEST(digitalRead, SWITCH_ON)
{
    switch_state = true;
    ASSERT_EQ(digitalRead(SWITCH), LOW);
}

TEST(digitalRead, SWITCH_OFF)
{
    switch_state = false;
    ASSERT_EQ(digitalRead(SWITCH), HIGH);
}

TEST(digitalRead, WATER_ON)
{
    water_state = true;
    ASSERT_EQ(digitalRead(WATER), LOW);
}

TEST(digitalRead, WATER_OFF)
{
    water_state = false;
    ASSERT_EQ(digitalRead(WATER), HIGH);
}

TEST(digitalRead, WATERLEVEL_ONON)
{
    water_level_state  = true;
    measure_current_wl = true;
    ASSERT_EQ(digitalRead(WATERLEVEL), LOW);
}

TEST(digitalRead, WATERLEVEL_ONOFF)
{
    water_level_state  = true;
    measure_current_wl = false;
    ASSERT_EQ(digitalRead(WATERLEVEL), HIGH);
}

TEST(digitalRead, WATERLEVEL_OFFON)
{
    water_level_state  = false;
    measure_current_wl = true;
    ASSERT_EQ(digitalRead(WATERLEVEL), HIGH);
}

TEST(digitalRead, WATERLEVEL_OFFOFF)
{
    water_level_state  = false;
    measure_current_wl = false;
    ASSERT_EQ(digitalRead(WATERLEVEL), HIGH);
}

TEST(digitalRead, MEASURE_WL_ON)
{
    measure_current_wl = true;
    ASSERT_EQ(digitalRead(MEASURE_WL), LOW);
}

TEST(digitalRead, MEASURE_WL_OFF)
{
    measure_current_wl = false;
    ASSERT_EQ(digitalRead(MEASURE_WL), HIGH);
}

TEST(Serial, println)
{
    Output Serial;
    Serial.print("String: ");
    Serial.println(" Done!");
    Serial.print(9999L);
    Serial.println(1000L);
    Serial.print(1.375F);
    Serial.print(5.357F);
    Serial.println("");
}

TEST(millis, 10s)
{
    unsigned long start = millis();

    cout << "Start!\n";
    while ((millis() - start) < 3000)
        ;
    cout << "Stop! - 3 s\n";
}

TEST(clock, setClock)
{
    DS3231 clock;
    clock.setDateTime(2019, 10, 21, 22, 6, 30);
    ASSERT_EQ(current_local_time.year, 2019);
    ASSERT_EQ(current_local_time.month, 10);
    ASSERT_EQ(current_local_time.day, 21);
    ASSERT_EQ(current_local_time.hour, 22);
    ASSERT_EQ(current_local_time.minute, 6);
    ASSERT_EQ(current_local_time.second, 30);
}

TEST(clock, getLocalTime)
{
    DS3231 clock;
    RTCDateTime time;
    current_local_time.year   = 2019;
    current_local_time.month  = 10;
    current_local_time.day    = 25;
    current_local_time.hour   = 22;
    current_local_time.minute = 5;
    current_local_time.second = 20;

    time = clock.getDateTime();

    ASSERT_EQ(time.year, 2019);
    ASSERT_EQ(time.month, 10);
    ASSERT_EQ(time.day, 25);
    ASSERT_EQ(time.hour, 22);
    ASSERT_EQ(time.minute, 5);
    ASSERT_EQ(time.second, 20);
}