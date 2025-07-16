Feature: Blink the LED

Scenario: Blink slow when proximity sensor is activated
  When I trigger the proximity sensor
  Then the LED is off for 900 milliseconds
  Then the LED is on for 900 milliseconds
  Then the LED is off for 900 milliseconds
  Then the LED is on for 900 milliseconds

Scenario: Blink faster when proximity sensor is activated again
  When I trigger the proximity sensor
  Then the LED is off for 800 milliseconds
  Then the LED is on for 800 milliseconds
  Then the LED is off for 800 milliseconds
  Then the LED is on for 800 milliseconds
