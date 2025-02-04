
Vdq = [0.0; 1.0];
C_ab_to_uvw = sqrt(2/3)*[1 0; -0.5, sqrt(3)/2; -0.5, -sqrt(3)/2];
deg_to_rad = pi/180;
PWM_values = [0;0;0];

for i = 0:360
  rotor_angle = i;
  C_dq_to_ab = [cos(rotor_angle*deg_to_rad), -sin(rotor_angle*deg_to_rad);
                sin(rotor_angle*deg_to_rad), cos(rotor_angle*deg_to_rad)];
  Vab = C_dq_to_ab*Vdq;
  Vuvw = C_ab_to_uvw*Vab;
  Vcm = -1.0*(max(Vuvw) + min(Vuvw))/2.0;
  Vuvw = (Vuvw + Vcm + 1/sqrt(2))/sqrt(2);

  PWM_values(:, i + 1) = Vuvw;
end

plot(0:360, PWM_values(1, :), 'linewidth', 2, 0:360, PWM_values(2, :),'linewidth', 2, 0:360, PWM_values(3, :), 'linewidth', 2)