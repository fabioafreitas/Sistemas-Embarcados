#include "Arduino.h"
#include "heltec.h"
#include <EEPROM.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

#define EEPROM_INITIAL_ADDRESS  (0)
#define BYTES_SIZE_SERVER       (41) // 40 caracteres + 1 do null terminator
#define BYTES_SIZE_DEVICEID     (11) // 10 caracteres + 1 do null terminator
#define EEPROM_SIZE             (BYTES_SIZE_SERVER + BYTES_SIZE_DEVICEID)

/*
 * Convenção que criei para salvar os dados na memória       
 * 
 *   |-----------| (0x0)
 *   |  Server   |  
 *   |-----------| (0x0 + serverNumBytes)
 *   |  DeviceID |
 *   |-----------| (0x0 + serverNumBytes + deviceIdNumBytes)
 *   |    ...    |
 *   
 */
#define INIT_ADDRESS_SERVER     (EEPROM_INITIAL_ADDRESS)
#define INIT_ADDRESS_DEVICEID   (EEPROM_INITIAL_ADDRESS + BYTES_SIZE_SERVER)


/* 
 *  Recebe uma string (char*) e a salva a partir de 
 *  um endereço inicial na eeprom (address). Além
 *  disso, é considerado um tamanho reservado de bytes, 
 *  para evitar do dado salvo sobrescrever dados indevidos
 *  em posições não alocadas.
 */
void saveStringInEEPROM(String str, int address, int numReservedBytes) {
  int len = str.length()+1;
  char arr[len];
  str.toCharArray(arr, len);
  
  EEPROM.begin(EEPROM_SIZE);
  int initAddr = address;
  int finalAddr = address + numReservedBytes;
  
  len = strlen(arr);
  Serial.println("-----------------------------------------------------------");
  if(len >= numReservedBytes) {
    Serial.println(String("[EEPROM - ESCRITA] Erro: A string \"" + String(arr) + "\" é muito grande, com " + len + " caracteres"));
    Serial.println(String("[EEPROM - ESCRITA] O length máximo permitido é de " + String(numReservedBytes-1) + ". O último espaço é reservado ao NULL TERMINATOR (ascii 0x0)"));
    EEPROM.end();
    return;
  }
  
  // "Enquanto String não terminou ou não alcançou endereço final reservado, faça"
  // i <= strlen(deviceid), o <= serve para garantir que o null terminator da string seja salvo
  for (int i = 0; i <= len; i++) {
    EEPROM.write(initAddr, arr[i]);
    initAddr += sizeof(char);
  }
  
  bool saveStatus = EEPROM.commit();
  if(saveStatus) {
    Serial.println(String("[EEPROM - ESCRITA] String \"" + String(arr) + "\" salva com sucesso"));
  } 
  else {
    Serial.println(String("[EEPROM - ESCRITA] Erro ao salvar a string \"" + String(arr) + "\""));
  }
  EEPROM.end();
}


String readStringFromEEPROM(int address, int numReservedBytes) {
  EEPROM.begin(EEPROM_SIZE);
  int i = 0;
  char charArray[numReservedBytes];
  
  int initAddr = address;
  int finalAddr = address + numReservedBytes;
  
  int current_char = EEPROM.read(initAddr);
  Serial.println("-----------------------------------------------------------");
  for (i = 0; current_char != NULL ; i++) {
    /* 
     * Verifica se a leitura ultrapassou o buffer reservado
     * 
     * Embora exista um mecanismo de segurança para evitar sobrescrever 
     * espaços não reservado, bugs podem ocorrer de outras fontes, logo
     * é melhor verificar para evitar a aparição de bugs latentes
     */
    if(initAddr >= finalAddr) {
      Serial.println("[EEPROM - LEITURA] Erro: o ponteiro de leitura ultrapassou a região de bytes reservados");
      return "none";
    }
    
    charArray[i] = current_char;
    initAddr += sizeof(char);
    current_char = EEPROM.read(initAddr);
  }
  charArray[i] = NULL;
  
  Serial.println(String("[EEPROM - LEITURA] Leitura concluida, String = \"" + String(charArray) + "\""));
  EEPROM.end();
  return String(charArray);
}

void setup() {
  Heltec.begin(false, false, true);
  Serial.begin(9600);

  String server = "123456789012345678901234567801234567890a";
  String deviceid = "cf2134";

  saveStringInEEPROM(server, INIT_ADDRESS_SERVER, BYTES_SIZE_SERVER);
  saveStringInEEPROM(deviceid, INIT_ADDRESS_DEVICEID, BYTES_SIZE_DEVICEID);

  String serv = readStringFromEEPROM(INIT_ADDRESS_SERVER, BYTES_SIZE_SERVER);
  String devi = readStringFromEEPROM(INIT_ADDRESS_DEVICEID, BYTES_SIZE_DEVICEID);
  
  Serial.println( serv );
  Serial.println( devi );
  
}

void loop() {}
