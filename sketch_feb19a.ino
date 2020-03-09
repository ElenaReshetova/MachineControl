const int Vleft = 3;
const int Dleft = 12;
const int Vright = 11;
const int Dright = 13;

void setup()
{               
  pinMode(Vleft, OUTPUT);
  pinMode(Dleft, OUTPUT);
  pinMode(Vright, OUTPUT);
  pinMode(Dright, OUTPUT);
  Serial.begin(115200);
}

int V, W, Vl, Vr, Vl_vol, Vr_vol; //от -100 до 100

void loop()
{
  if (Serial.available())
  {
    V = Serial.parseInt();
    W = Serial.parseInt();
    Serial.print("V = "); Serial.print(V); Serial.print("; W = "); Serial.println(W);
    Vl = V + W; //от -100 до 100
    Vr = V - W; //от -100 до 100
    Serial.print("Vl = "); Serial.print(Vl); Serial.print("; Vr = "); Serial.println(Vr);
    
    if (Vl<0)
      digitalWrite(Dleft, LOW);
    else
      digitalWrite(Dleft, HIGH);
    if (Vr<0)
      digitalWrite(Dright, LOW);
    else
      digitalWrite(Dright, HIGH);

    Vl_vol = (abs(Vl) * 2.55);
    Vr_vol = (abs(Vr) * 2.55);
    
    analogWrite(Vleft, Vl_vol);
    analogWrite(Vright, Vr_vol);
    Serial.print("L = "); 
    if (Vl<0)
      Serial.print('-');
    Serial.print(Vl_vol); Serial.print("; R = ");
    if (Vr<0)
      Serial.print('-');
    Serial.println(Vr_vol);
    Serial.println();
  }
}
