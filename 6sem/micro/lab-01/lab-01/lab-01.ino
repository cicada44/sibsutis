char keyboardKeys[][4] = {{'1', '4', '7', '*'}, {'2', '5', '8', '0'}, {'3', '6', '9', '#'}, {'A', 'B', 'C', 'D'}};

void chooseChar(char keyboardKeys[4])
{
    if (!(PINB & (1<<PINB3)))
      Serial.println(keyboardKeys[0]);
    if (!(PINB & (1<<PINB2)))
      Serial.println(keyboardKeys[1]);
    if (!(PINB & (1<<PINB1)))
      Serial.println(keyboardKeys[2]);
    if (!(PINB & (1<<PINB0)))
      Serial.println(keyboardKeys[3]);
}

int main()
{
  Serial.begin(9600);
  Serial.println("s");
  
  PORTB |= (1<<PORTB0);
  PORTB |= (1<<PORTB1);
  PORTB |= (1<<PORTB2);
  PORTB |= (1<<PORTB3);
  
  DDRD |= (1<<DDD4);
  DDRD |= (1<<DDD5);
  DDRD |= (1<<DDD6);
  DDRD |= (1<<DDD7);
  
  while (1)
  {
    PORTD &= ~(1<<DDD7);
    PORTD |= (1<<DDD6);
    PORTD |= (1<<DDD5);
    PORTD |= (1<<DDD4);
    chooseChar(keyboardKeys[0]);
    PORTD |= (1<<DDD7);
    PORTD &= ~(1<<DDD6);
    chooseChar(keyboardKeys[1]);
    PORTD |= (1<<DDD6);
    PORTD &= ~(1<<DDD5);
    chooseChar(keyboardKeys[2]);
    PORTD |= (1<<DDD5);
    PORTD &= ~(1<<DDD4);
    chooseChar(keyboardKeys[3]);
  }
}
