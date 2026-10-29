void startTone(int buzzerPin){
  tone(buzzerPin, 1000);
  delay(200);
  tone(buzzerPin, 0);
}

void badTone(int buzzerPin){
  tone(buzzerPin, 500);
  delay(200);
  tone(buzzerPin, 0);
}

void goodTone(int buzzerPin){
  tone(buzzerPin, 2000);
  delay(200);
  tone(buzzerPin, 0);
}

void proximityTone(int buzzerPin, double haversineDistance){
  if((int)millis() % (int)haversineDistance == 0){
    tone(buzzerPin, 3000);
    delay(200);
    tone(buzzerPin, 0);
  }
}
