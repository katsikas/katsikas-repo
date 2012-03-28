% COMMDVBT_TABLEGEN Generate interleaver and modulator lookup tables for 
% COMMDVBT demo

%   Copyright 1996-2008 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $  $Date: 2010/08/29 23:23:45 $
%
% Set the sample time 
%
Ts = 0.000224*2176/9072/188;

%
% Section numbers refer to the ETSI DVB-T Standard,
% EN 300 744 V1.1.2 (1997-08)
%

%
% Compute lookup table for inner bit-wise interleaver 
% as per section 4.3.4.1
%

% Initial table setup
dvb_bit_int_table = 1:756;
dvb_bit_int_table = reshape(dvb_bit_int_table, 6, 126);

% 64-QAM non-hierarchical demultiplexing
dvb_bit_int_table = dvb_bit_int_table([1 4 2 5 3 6],:);

% Six individual interleavers
dvb_bit_int_table(1,:) = dvb_bit_int_table(1,mod([0:125] +  0,126) + 1);
dvb_bit_int_table(2,:) = dvb_bit_int_table(2,mod([0:125] + 63,126) + 1);
dvb_bit_int_table(3,:) = dvb_bit_int_table(3,mod([0:125] +105,126) + 1);
dvb_bit_int_table(4,:) = dvb_bit_int_table(4,mod([0:125] + 42,126) + 1);
dvb_bit_int_table(5,:) = dvb_bit_int_table(5,mod([0:125] + 21,126) + 1);
dvb_bit_int_table(6,:) = dvb_bit_int_table(6,mod([0:125] + 84,126) + 1);

% Flatten matrix into lookup table
dvb_bit_int_table = dvb_bit_int_table(:);

%
% Compute lookup table for inner symbol interleaver 
% as per section 4.3.4.2
%

% Following Figure 8a and accompanying equations
q = 0;
h = zeros(1,2048);
R = zeros(1,10);
for indx = 0:2047,
   if indx == 2,
      R(1) = 1;
   end
   Rsum = R(3)*2^9+R(6)*2^8+R(9)*2^7+R(4)*2^6+...                             
      R(8)*2^5+R(1)*2^4+R(2)*2^3+R(5)*2^2+R(7)*2^1+R(10)*2^0;             
   h(q+1) = rem(indx,2)*2^10+Rsum;
   if h(q+1)<1512,
      q = q + 1;
   end
   R = [R(2:10) xor(R(1),R(4))];
end
dvb_sym_int_table = h(1:1512)+1;

% Clear unnecessary variables from workspace
clear R Rsum h indx q

% Expand table to accommodate 6-bit words
dvb_sym_int_table = [dvb_sym_int_table*6-5; 
	                 dvb_sym_int_table*6-4;
					 dvb_sym_int_table*6-3;
					 dvb_sym_int_table*6-2;
					 dvb_sym_int_table*6-1; 
					 dvb_sym_int_table*6];
				 
% Flatten matrix into lookup table
dvb_sym_int_table = dvb_sym_int_table(:);

%
% Compute lookup table for 64-QAM non-hierarchical modulator  
% as per section 4.3.5
%

% Reading the values from Figure 9a
dvbt_qam = [ 7 + 7i
            -7 + 7i
             7 - 7i
            -7 - 7i
             1 + 7i
            -1 + 7i
             1 - 7i
            -1 - 7i
             7 + 1i
            -7 + 1i
             7 - 1i
            -7 - 1i
             1 + 1i
            -1 + 1i
             1 - 1i
            -1 - 1i
             5 + 7i
            -5 + 7i
             5 - 7i
            -5 - 7i
             3 + 7i
            -3 + 7i
             3 - 7i
            -3 - 7i
             5 + 1i
            -5 + 1i
             5 - 1i
            -5 - 1i
             3 + 1i
            -3 + 1i
             3 - 1i
            -3 - 1i
             7 + 5i
            -7 + 5i
             7 - 5i
            -7 - 5i
             1 + 5i
            -1 + 5i
             1 - 5i
            -1 - 5i
             7 + 3i
            -7 + 3i
             7 - 3i
            -7 - 3i
             1 + 3i
            -1 + 3i
             1 - 3i
            -1 - 3i
             5 + 5i
            -5 + 5i
             5 - 5i
            -5 - 5i
             3 + 5i 
            -3 + 5i 
             3 - 5i 
            -3 - 5i 
             5 + 3i
            -5 + 3i
             5 - 3i
            -5 - 3i
             3 + 3i
            -3 + 3i
             3 - 3i
            -3 - 3i ];

% Normalization factor from Section 4.4
dvbt_qam = dvbt_qam/sqrt(42);

% 64-QAM Constellation mapping from Figure 9a. Note that the bit words are
% flipped. This mapping is used by alternative version of the demo.
dvbt_const_mapping = [ ...
    1   17  21   5   4  20  16   0;...
    33  49  53  37  36  52  48  32;... 
    41  57  61  45  44  60  56  40;... 
     9  25  29  13  12  28  24   8;... 
    11  27  31  15  14  30  26  10;... 
    43  59  63  47  46  62  58  42;... 
    35  51  55  39  38  54  50  34;... 
     3  19  23   7   6  22  18   2 ...
               ];

dvbt_mapping = dvbt_const_mapping(:);
