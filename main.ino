#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// =====================================================
// PCA9685
// =====================================================

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const int SERVO1_CH = 3;   // pointer
const int SERVO2_CH = 1;   // ring
const int SERVO3_CH = 2;   // middlel
const int SERVO4_CH = 0;   // pinky

const int SERVO_MIN_US = 1000;
const int SERVO_MAX_US = 2000;

// =====================================================
// TIMING
// =====================================================

bool ENABLE_TRANSITIONS = true;

const unsigned long TRANSITION_TIME  = 300;   // ms
const unsigned long LETTER_HOLD_TIME = 800;   // ms

// wave timing
const unsigned long SPACE_STEP_TIME  = 80;
const unsigned long SPACE_PAUSE_TIME = 120;

// =====================================================
// CURRENT HAND STATE
// =====================================================

int currentP1 = 1500;
int currentP2 = 1500;
int currentP3 = 1500;
int currentP4 = 1500;

// =====================================================
// ALPHABET DATABASE
// =====================================================

struct LetterPose
{
    char letter;
    int p1;
    int p2;
    int p3;
    int p4;
};

LetterPose alphabet[] =
{
    {'A',2000,2000,2000,2000},
    {'B',1000,1000,1000,1000},
    {'C',1766,1677,1731,1694},
    {'D',1000,2000,2000,2000},
    {'E',2000,2000,2000,2000},
    {'F',1871,1000,1000,1000},
    {'G',1616,2000,2000,2000},
    {'H',1673,2000,1662,2000},
    {'I',2000,2000,2000,1000},

    // J unavailable

    {'K',1000,2000,1000,2000},
    {'L',1000,2000,2000,2000},

    {'M',2000,2000,2000,2000},
    {'N',1850,2000,1850,2000},

    {'O',1500,1500,1500,1500},
    {'P',1590,2000,1760,2000},
    {'Q',1815,2000,2000,2000},

    {'R',1400,2000,1000,2000},
    {'S',2000,2000,2000,2000},
    {'T',1888,2000,1888,2000},

    {'U',1000,2000,1000,2000},
    {'V',1000,2000,1000,2000},
    {'W',1000,1000,1000,2000},

    {'X',1570,2000,1858,2000},
    {'Y',2000,2000,2000,1000}

    // Z unavailable
};

const int NUM_LETTERS =
    sizeof(alphabet)/sizeof(alphabet[0]);

// =====================================================
// SERVO OUTPUT
// =====================================================

void writeServoUS(uint8_t channel,
                  int microseconds)
{
    microseconds =
        constrain(microseconds,
                  SERVO_MIN_US,
                  SERVO_MAX_US);

    uint16_t ticks =
        (uint32_t)microseconds *
        4096UL /
        20000UL;

    pwm.setPWM(channel,0,ticks);
}

// =====================================================
// SMOOTH MOTION
// =====================================================

void moveToPose(
    int targetP1,
    int targetP2,
    int targetP3,
    int targetP4,
    unsigned long moveTime)
{
    if(!ENABLE_TRANSITIONS)
    {
        writeServoUS(SERVO1_CH,targetP1);
        writeServoUS(SERVO2_CH,targetP2);
        writeServoUS(SERVO3_CH,targetP3);
        writeServoUS(SERVO4_CH,targetP4);

        currentP1 = targetP1;
        currentP2 = targetP2;
        currentP3 = targetP3;
        currentP4 = targetP4;

        return;
    }

    const int STEPS = 25;

    int startP1 = currentP1;
    int startP2 = currentP2;
    int startP3 = currentP3;
    int startP4 = currentP4;

    for(int i=1;i<=STEPS;i++)
    {
        float t = (float)i/STEPS;

        int p1 = startP1 +
                 (targetP1-startP1)*t;

        int p2 = startP2 +
                 (targetP2-startP2)*t;

        int p3 = startP3 +
                 (targetP3-startP3)*t;

        int p4 = startP4 +
                 (targetP4-startP4)*t;

        writeServoUS(SERVO1_CH,p1);
        writeServoUS(SERVO2_CH,p2);
        writeServoUS(SERVO3_CH,p3);
        writeServoUS(SERVO4_CH,p4);

        delay(moveTime/STEPS);
    }

    currentP1 = targetP1;
    currentP2 = targetP2;
    currentP3 = targetP3;
    currentP4 = targetP4;
}

// =====================================================
// LETTER SIGNING
// =====================================================

bool signLetter(char c)
{
    c = toupper(c);

    for(int i=0;i<NUM_LETTERS;i++)
    {
        if(alphabet[i].letter == c)
        {
            Serial.print("Signing: ");
            Serial.println(c);

            moveToPose(
                alphabet[i].p1,
                alphabet[i].p2,
                alphabet[i].p3,
                alphabet[i].p4,
                TRANSITION_TIME);

            delay(LETTER_HOLD_TIME);

            return true;
        }
    }

    Serial.print("Unknown letter: ");
    Serial.println(c);

    return false;
}

void wordSpaceAnimation()
{
    Serial.println("[new word]");

    const int O = 1500;
    const int C = 2000;

    const unsigned long WAVE = 70;

    // pointer
    moveToPose(C,O,O,O,WAVE);

    // pointer + middle
    moveToPose(C,O,C,O,WAVE);

    // middle + ring
    moveToPose(O,C,C,O,WAVE);

    // ring + pinky
    moveToPose(O,C,O,C,WAVE);

    // pinky
    moveToPose(O,O,O,C,WAVE);

    // reverse
    moveToPose(O,C,O,C,WAVE);
    moveToPose(O,C,C,O,WAVE);
    moveToPose(C,O,C,O,WAVE);
    moveToPose(C,O,O,O,WAVE);

    moveToPose(O,O,O,O,WAVE);

    delay(150);
}

// =====================================================
// PHRASE SIGNING
// =====================================================

void signPhrase(String phrase)
{
    phrase.toUpperCase();

    Serial.println();
    Serial.print("Phrase: ");
    Serial.println(phrase);
    Serial.println();

    for(int i=0;i<phrase.length();i++)
    {
        char c = phrase[i];

        if(c == ' ')
        {
            Serial.println("[space]");\
            wordSpaceAnimation();
            // delay(WORD_PAUSE_TIME);
        }
        else
        {
            signLetter(c);
        }
    }

    Serial.println();
    Serial.println("Finished.");
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(9600);

    Wire.begin();

    pwm.begin();
    pwm.setPWMFreq(50);

    delay(100);

    // neutral startup position
    writeServoUS(SERVO1_CH,1500);
    writeServoUS(SERVO2_CH,1500);
    writeServoUS(SERVO3_CH,1500);
    writeServoUS(SERVO4_CH,1500);

    currentP1 = 1500;
    currentP2 = 1500;
    currentP3 = 1500;
    currentP4 = 1500;

    Serial.println();
    Serial.println("=========================");
    Serial.println("ASL HAND READY");
    Serial.println("=========================");
    Serial.println();
    Serial.println("Enter a phrase:");
    Serial.println("Example:");
    Serial.println("HELLO WORLD");
    Serial.println();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
    if(Serial.available())
    {
        String phrase =
            Serial.readStringUntil('\n');

        phrase.trim();

        if(phrase.length() > 0)
        {
            signPhrase(phrase);
        }

        Serial.println();
        Serial.println("Enter another phrase:");
    }
}