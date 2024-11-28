#include <iostream>
#include <cmath>
using namespace std;

float getTorqueFromThrottle(int t, int input[]) {
    float output = 0;

    int sensor1 = (input[1] * 256) + input[2]; // MSB ile LSB yi birleştirme
    int sensor2 = (input[3] * 256) + input[4];
    
    // Güvenlik Kontrolleri
    if (abs(sensor1 - sensor2) > 65536 * 0.1) // %10'dan fazla fark olursa
        return 0; 
    if (sensor1 < 65536 * 0.1 && sensor2 < 65536 * 0.1) // %10'dan az pedala basilirsa
        return 0; 
    float average = (sensor1 + sensor2) / 2.0; // Torku verecek değer net belirtilmemis ama ortalamasi oldugunu varsaydim
    
    output = (average - 6553.6f) * (t / (65536.0f - 6553.6f)); /* Basit bir mapleme fonksiyonu, normalde fonksiyonu ayri tanımlamak 
    daha temiz bir kod olurdu */

    return output; 
}

int main() {
    
    int t;
    int inputArr[4]; 

    cin >> t;

    for (int i = 1; i < 4; i++) { 
        cin >> inputArr[i];
    }

    cout << getTorqueFromThrottle(t, inputArr);
    
    return 0;
}
