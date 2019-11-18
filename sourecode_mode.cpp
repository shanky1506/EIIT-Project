void loop()
{
  if(a==0)
  {
    //delay at which interval the data is required
    delay(10);
    a=1;
  }
  else
  {

    /* Reference Sensors*/
    digitalWrite(r_trigPin, HIGH);
    delayMicroseconds(2);

    // Set the trigPin on HIGH state for 10 micro seconds
    digitalWrite(r_trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(r_trigPin, HIGH);

    // Read the echoPin, return the sound wave travel time for reference sensor in microseconds
    r_duration = pulseIn(r_echoPin, HIGH);
    r_distance= (r_duration*0.034/2);


  /* Main Sensor*/
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin,LOW);

    m_duration =pulseIn(m_echoPin, HIGH);
    m_distance= (m_duration*0.034/2);

    delay(1000);
    m_distance=(m_distance*r_distance)/10;
    b[a-1]=m_distance;
    a++;

    //Print Output to Serial Monitor
    Serial.println(m_distance);

    // Mode calculation
    if(a==21)
    {
      double maxCount = 0;
      maxValue=0;
      Serial.println(" ");
      for (int i = 0; i < a; ++i)
      {
        float count = 0;

        for (int j = 0; j < a; ++j)
        {
          if (b[j] == b[i])
            ++count;
        }

         if (count > maxCount)
         {
            maxCount = count;
            maxValue = b[i];
         }
      }
      Serial.print("value  ");
      Serial.println(maxValue);

      //Angular data calculation
      a=0;
      double q=pow(maxValue,2);
      double w =pow(R,2);
      ang=acos(q/(w-1));
    }
  }
}
