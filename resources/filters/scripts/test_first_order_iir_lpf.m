deltaT = 0.1;
time_constant = 1;

new_output = 0.0;
previous_input = 0.0;
input = 0.0;
previous_output = 0.0;

length = 100

for i = 2:length
  if i == 20
    input = 1.0;
  endif
  unscalled_output = input + previous_input + (2.0*time_constant/deltaT - 1.0)*previous_output;
  new_output(i) = (1.0/(1.0 + 2.0*time_constant/deltaT))*unscalled_output;
  previous_input = input;
  previous_output = new_output(i);
end

plot((1:length)*deltaT, new_output)
