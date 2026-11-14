void startTone(int buzzerPin){
  tone(buzzerPin, 1000);
  delay(200);
  tone(buzzerPin, 0);
}

void badTone(int buzzerPin){
  tone(buzzerPin, 500);
  delay(20);

  tone(buzzerPin, 0);
}

void goodTone(int buzzerPin){
  tone(buzzerPin, 2000);
  delay(200);
  tone(buzzerPin, 0);
}

void proximityTone(int buzzerPin, double haversineDistance, unsigned long *dMillis){
  if(haversineDistance < 5){
    tone(buzzerPin, 3000);
    delay(200);
    tone(buzzerPin, 0);
  }
  else if(haversineDistance < 20 && *dMillis >= 600.0){
    *dMillis = 0;
    tone(buzzerPin, 3000);
    delay(200);
    tone(buzzerPin, 0);
  }
  else if(haversineDistance < 50 && *dMillis >= 3000.0){
    *dMillis = 0;
    tone(buzzerPin, 3000);
    delay(200);
    tone(buzzerPin, 0);
  }
}
