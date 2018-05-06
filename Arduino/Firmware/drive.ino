// 1
void forwardLeft(int PWM) {
  if (STATUS == FORWARD_LEFT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = FORWARD_LEFT;
  forwardLeftUnsafe(PWM);
}

// 2
void forward(int PWM) {
  if (STATUS == FORWARD) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = FORWARD;
  forwardUnsafe(PWM);
}

// 3
void forwardRight(int PWM) {
  if (STATUS == FORWARD_RIGHT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = FORWARD_RIGHT;
  forwardRightUnsafe(PWM);
}

// 4
void left(int PWM) {
  if (STATUS == LEFT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = LEFT;
  leftUnsafe(PWM);
}

// 5
void stop() {
  STATUS = STOP;
  digitalWrite( MOTOR_LEFT_DIR, LOW );
  digitalWrite( MOTOR_LEFT_PWM, LOW );
  digitalWrite( MOTOR_RIGHT_DIR, LOW );
  digitalWrite( MOTOR_RIGHT_PWM, LOW );
}

// 6
void right(int PWM) {
  if (STATUS == RIGHT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = RIGHT;
  rightUnsafe(PWM);
}

// 7
void backwardLeft(int PWM) {
  if (STATUS == BACKWARD_LEFT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = BACKWARD_LEFT;
  backwardLeftUnsafe(PWM);
}

// 8
void backward(int PWM) {
  if (STATUS == BACKWARD) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = BACKWARD;
  backwardUnsafe(PWM);
}

// 9
void backwardRight(int PWM) {
  if (STATUS == BACKWARD_RIGHT) return;
  if (STATUS != STOP) {
    stop();
    delay( DIR_DELAY );
  }
  STATUS = BACKWARD_RIGHT;
  backwardRightUnsafe(PWM);
}
