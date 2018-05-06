boolean canGoForward() {
  return (ir_left == LOW && ir_right == LOW && (distance == 0 || distance > 5));
}

boolean isGoingForward() {
  switch (STATUS) {
    case FORWARD:
    case FORWARD_LEFT:
    case FORWARD_RIGHT:
      return true;
    default:
      return false;
  }
}

// 1
void forwardLeftSafe(int PWM) {
  if (!canGoForward()) {
    stop();
    return;
  }
  forwardLeft(PWM);
}

// 2
void forwardSafe(int PWM) {
  if (!canGoForward()) {
    stop();
    return;
  }
  forward(PWM);
}

// 3
void forwardRightSafe(int PWM) {
  if (!canGoForward()) {
    stop();
    return;
  }
  forwardRight(PWM);
}
