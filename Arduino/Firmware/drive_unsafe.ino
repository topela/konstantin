// 1
void forwardLeftUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, HIGH ); // direction = forward
  digitalWrite( MOTOR_RIGHT_DIR, HIGH ); // direction = forward
  analogWrite( MOTOR_LEFT_PWM, 255 - PWM ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, 255 - (PWM / 2) ); // PWM speed
}

// 2
void forwardUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, HIGH ); // direction = forward
  digitalWrite( MOTOR_RIGHT_DIR, HIGH ); // direction = forward
  analogWrite( MOTOR_LEFT_PWM, 255 - PWM ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, 255 - PWM ); // PWM speed
}

// 3
void forwardRightUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, HIGH ); // direction = forward
  digitalWrite( MOTOR_RIGHT_DIR, HIGH ); // direction = forward
  analogWrite( MOTOR_LEFT_PWM, 255 - (PWM / 2) ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, 255 - PWM ); // PWM speed
}

// 4
void leftUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, HIGH );    // direction = forward
  digitalWrite( MOTOR_RIGHT_DIR, LOW );     // direction = reverse
  analogWrite( MOTOR_LEFT_PWM, 255 - PWM ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, PWM );      // PWM speed
}

// 6
void rightUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, LOW );    // direction = forward
  digitalWrite( MOTOR_RIGHT_DIR, HIGH );   // direction = reverse
  analogWrite( MOTOR_LEFT_PWM, PWM );     // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, 255 - PWM ); // PWM speed
}

// 7
void backwardLeftUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, LOW ); // direction = reverse
  digitalWrite( MOTOR_RIGHT_DIR, LOW ); // direction = reverse
  analogWrite( MOTOR_LEFT_PWM, PWM ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, PWM / 2); // PWM speed
}

// 8
void backwardUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, LOW ); // direction = reverse
  digitalWrite( MOTOR_RIGHT_DIR, LOW ); // direction = reverse
  analogWrite( MOTOR_LEFT_PWM, PWM ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, PWM ); // PWM speed
}

// 9
void backwardRightUnsafe(int PWM) {
  digitalWrite( MOTOR_LEFT_DIR, LOW ); // direction = reverse
  digitalWrite( MOTOR_RIGHT_DIR, LOW ); // direction = reverse
  analogWrite( MOTOR_LEFT_PWM, PWM / 2 ); // PWM speed
  analogWrite( MOTOR_RIGHT_PWM, PWM); // PWM speed
}
