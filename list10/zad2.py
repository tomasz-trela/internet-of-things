#!/usr/bin/env python3
import time
import datetime
import RPi.GPIO as GPIO
from mfrc522 import MFRC522

# --- Hardware Configuration ---
# Adjust these pins based on your specific lab wiring
BUZZER_PIN = 23
LED_PIN = 18 

def setup_gpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(BUZZER_PIN, GPIO.OUT)
    GPIO.setup(LED_PIN, GPIO.OUT)
    # Ensure they start OFF
    GPIO.output(BUZZER_PIN, GPIO.LOW)
    GPIO.output(LED_PIN, GPIO.LOW)

def feedback_signal():
    """Triggers sound and visual feedback """
    # Turn ON
    GPIO.output(BUZZER_PIN, GPIO.HIGH)
    GPIO.output(LED_PIN, GPIO.HIGH)
    
    time.sleep(0.15) # Short beep
    
    # Turn OFF
    GPIO.output(BUZZER_PIN, GPIO.LOW)
    GPIO.output(LED_PIN, GPIO.LOW)

def rfid_registration_loop():
    reader = MFRC522()
    
    # State variable to track if a card is currently being held
    card_present_flag = False
    
    print("RFID Reader Active. Place card to register...")
    print("Press Ctrl+C to stop.")

    try:
        while True:
            # 1. Check for card presence
            (status, TagType) = reader.MFRC522_Request(reader.PICC_REQIDL)

            if status == reader.MI_OK:
                # 2. Card detected, get UID
                (status, uid) = reader.MFRC522_Anticoll()
                
                if status == reader.MI_OK:
                    # Logic: Only register if we weren't already holding a card
                    if not card_present_flag:
                        # Process the UID
                        uid_string = ".".join(str(x) for x in uid)
                        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
                        
                        # Log registration [cite: 209]
                        print(f"[REGISTERED] Time: {timestamp} | UID: {uid_string}")
                        
                        # Trigger feedback
                        feedback_signal()
                        
                        # Set flag to prevent immediate re-read 
                        card_present_flag = True
            else:
                # 3. If Request fails, the card is no longer in range.
                # Reset the flag so a new (or same) card can be read again.
                card_present_flag = False
            
            time.sleep(0.05) # Small delay to reduce CPU usage

    except KeyboardInterrupt:
        print("\nStopping RFID Reader...")
        GPIO.cleanup()

if __name__ == "__main__":
    setup_gpio()
    rfid_registration_loop()