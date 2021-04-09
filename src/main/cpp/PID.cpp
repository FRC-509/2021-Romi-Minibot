double PID(double error, double Kp){
  double p;
  p = Kp*error;
  return p;
}