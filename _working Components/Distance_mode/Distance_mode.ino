void setup()
{
//    int numbers[] = {1, 2, 3, 2, 1, 1, 1, 3, 4, 5, 2};
//    Serial.println(mode(numbers));
}


int mode(int array[]) {
    int modeMap[sizeof(array)];
    int maxEl = array[0];
    int maxCount = 1;

    for (int i = 0; i < sizeof(array); i++) {
        int el = array[i];
        if (modeMap[el] == 0) {
            modeMap[el] = 1;
        }
        else {
            modeMap[el]++;
        }

        if (modeMap[el] > maxCount) {
            maxEl = el;
            maxCount = modeMap[el];
        }
    }
    return maxEl;
}

void loop()
{
  int numbers[] = {1, 2, 3, 2, 1, 1, 1, 3, 4, 5, 2};
    Serial.println(mode(numbers));
  
}
