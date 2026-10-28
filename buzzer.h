void startTone(int buzzerPin){
  tone(buzzerPin, 1000);
  delay(200);
  tone(buzzerPin, 500);
  delay(200);
  tone(buzzerPin, 2000);
  delay(200);
  tone(buzzerPin, 0);
}

void badTone(int buzzerPin){
  tone(buzzerPin, 1000);
  delay(500);
  tone(buzzerPin, 500);
  delay(500);
  tone(buzzerPin, 200);
  delay(500);
  tone(buzzerPin, 0);
}

void goodTone(int buzzerPin){
  tone(buzzerPin, 1000);
  delay(200);
  tone(buzzerPin, 1250);
  delay(200);
  tone(buzzerPin, 1500);
  delay(200);
  tone(buzzerPin, 2000);
  delay(200);
  tone(buzzerPin, 0);
}
