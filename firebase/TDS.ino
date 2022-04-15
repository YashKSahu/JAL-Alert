


// caliculating TDS
float Update_TDS(double Tds_volt){
  
  double Tds_comp_coeff = 1.0+0.02*(Temp_C-25.0);
  double Comp_volt = Tds_volt/Tds_comp_coeff;

  double tds_value = (133.42*Comp_volt*Comp_volt*Comp_volt - 255.86*Comp_volt*Comp_volt + 857.39*Comp_volt)*0.25;

  return tds_value/2;

}
