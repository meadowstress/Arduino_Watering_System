//pins
const short PUMP = A0;
const short SWITCH = 7;
const short WATER = 3;

//states
bool pre_state_water = false;
bool current_state_water = false;
bool switch_on = false;
bool water_on = false;
bool timer_on = false;

unsigned long const t_half_can = 15000;

//function headers
bool State_Switch(int input);
void State_Water();
bool Hold_State(unsigned long  hold_time);
int Pump_Water(unsigned long pump_time);


void setup() // Enable on Hardware
{
  pinMode(PUMP, OUTPUT);  // Enable on Hardware
  pinMode(SWITCH, INPUT_PULLUP);  // Enable on Hardware
  pinMode(WATER, INPUT_PULLUP);  // Enable on Hardware
  Serial.begin(9600);  // Enable on Hardware
  

  digitalWrite(PUMP, HIGH); //default no pumping enabled

  //prevent different states when water switch is on
  if (digitalRead(WATER) == LOW)
  {
    pre_state_water = true;
    current_state_water = true;
  }
} //Enable on Hardware




void loop() // Enable on Hardware
{
  // state logics
  switch_on = State_Switch(digitalRead(SWITCH));
  State_Water();

  // function execution
  if (switch_on && water_on)
  {
    Serial.println("Pump_Water single Function!");
    Pump_Water(t_half_can);
  }
}

//Switch logic
bool State_Switch(int input)
{
  bool state;
  // switch logic
  if (input == LOW)
  {
    state = true;
  }
  else
  {
    state = false;
  }
  return state;
}


void State_Water()
{
  if (digitalRead(WATER) == LOW)
  {
    current_state_water = true;
  }
  else
  {
    current_state_water = false;
  }

  if (current_state_water != pre_state_water)
  {
    water_on = true;
    pre_state_water = current_state_water;
  }
  else
  {
    water_on = false;
  }
}


// Hold logic

bool Hold_State(unsigned long  hold_time)
{

  bool state_flag = true;
  unsigned long start_time = millis();
  unsigned long elapsed_time = 0;
  int i = 0;

  do
  {
    i++;
    switch_on = State_Switch(digitalRead(SWITCH));

    elapsed_time = (millis() - start_time);
    if ( (elapsed_time > hold_time) || switch_on == false)
    {
      state_flag = false;
    }
  } while (state_flag);

  // test if hold time has been elapsed regularly
  // var i is only necessary for time simulation with high factors
  if((elapsed_time > hold_time) && i > 1)
    return true;
  else
    return false;
}

int Pump_Water(unsigned long pump_time)
{
  bool water_flag = false;

  Serial.println("Pump Water!");
  digitalWrite(PUMP, LOW); //pumping starts
  water_flag = Hold_State(pump_time);
  digitalWrite(PUMP, HIGH); // pumping ends
  
  if(water_flag==true)
    return(1);
  else
    return(0);
}
