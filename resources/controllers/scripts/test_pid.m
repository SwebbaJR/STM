
1;

function saturated_output = saturate_output(unsaturated_output)
  saturated_output = max(-10, min(unsaturated_output, 10));
endfunction

function output = anti_windup(saturated_output, proportional_output, derivative_output, ki)
  if ki != 0
      output = (saturated_output - proportional_output - derivative_output) / ki;
  else
      output = 0; % Avoid division by zero
  endif
endfunction

deltaT = 0.01;
time_constant = 1;
cl_time_constant = 0.2
time_constant_tustin = 0.07;

x = 0;
u = 0;

reference = 0;

Kp = 15.0;
Ki = 120.0;
Kd = 0.5;

C = pid(Kp, Ki, Kd);

integral_error = 0;
previous_error = 0;
previous_derivative = 0;

length = 1000;

new_output = 0.0;
previous_input = 0.0;
input = 0.0;
previous_output = 0.0;

G = tf(1, [time_constant, 1]);

CL = feedback(G*C, 1)

for i = 2:length
    x(i) = exp(-deltaT/time_constant)*x(i-1) + (1-exp(-deltaT/time_constant))*u(i-1);

    if i == 20
      reference = 1;
    endif

    measurement = x(i);

    error = reference + (rand(1) - 0.5)*0.1 - measurement;

    % Integral state using Tustin transform
    integral_error += deltaT/2.0*(error + previous_error);

    % Derivative termin using Tustin transform
    derivative = 2.0/deltaT*(error - previous_error) - previous_derivative

    % Tustin filter
    unscalled_output = derivative + previous_derivative + (2.0*time_constant_tustin/deltaT - 1.0)*previous_output;
    new_output(i) = (1.0/(1.0 + 2.0*time_constant_tustin/deltaT))*unscalled_output;
    previous_input = input;
    previous_output = new_output(i);

    % Compute controller compontents
    proportional_output = Kp*error;
    integral_output = Ki*integral_error;
    derivative_output = Kd*new_output(i);
    unsaturated_output = proportional_output + integral_output + derivative_output;

    % Saturate output
    u(i) = saturate_output(unsaturated_output);
    u(i);

    % Anti-windup: Adjust integral term if output is saturated
    if (u(i) != unsaturated_output)
        integral_error = anti_windup(u(i), proportional_output, derivative_output, Ki);
    endif

    previous_error = error;
    previous_derivative = derivative;

end
figure(1)
subplot(2,1,1)
plot((1:length)*deltaT,x)
subplot(2,1,2)
plot((1:length)*deltaT,u)

figure(2)
step(CL);





