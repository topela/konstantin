boolean canGoForward() {
  return (ir_left == LOW && ir_right == LOW && (distance == 0 || distance > 5));
}

void forwardSafe(int PWM) {
  if (!canGoForward()) {
    stop();
    return;
  }
  forward(PWM);
}
