
1;

A = [2, -3;
    4, -5];

B = [2; 3];

Cz = [0, 1];

Ae = [A, zeros(2,1);
      Cz, zeros(1,1)];

Be = [B; zeros(1,1)];

poles = [-0.1, -10, -10];

C_mat = zeros(3,3);

A_mult = eye(3);

for i = 1:3
  C_mat(:, i) = A_mult*Be;
  A_mult = A_mult*Ae;
end


det(C_mat)

F = place(Ae, Be, poles);

F_p = F(1, 1:2)
F_i = F(1,3)

sim_length = 100000;
dt = 0.001;

z = 0;

ref = 1;

x = zeros(2, sim_length);

dz_prev = 0;

for i = 2:sim_length

  % Control update
  dz = Cz*x(:, i-1) - ref;
  z = z + dt/2 * (dz + dz_prev);
  u = -F_p*x(:, i-1) - F_i*z;
  dz_prev = dz;

  % Update states using full augmented system
  dx = A*x(:, i-1) + B*u;
  % Integrate using Euler's method
  x(:, i) = x(:, i-1) + dt * dx;

  if i > sim_length/2
    ref = -1;
  endif
end

plot((1:sim_length)*dt, x(2,:))
