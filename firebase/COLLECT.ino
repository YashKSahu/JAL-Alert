


void Collect_sesnor_data(void){
  for(int i = 0;i<40;i++){
    PH_array[i]   = analogRead(PH_pin);
    Tds_array[i]  = analogRead(Tds_pin);
    delay(10);
  }
}
