# Comparison of Prefix Sum Method

I've measured the elapsed time and the mean absolute error for the various methods of computing Prefix Sum of an array of 1M floats.

## Compiled with SSE2 option

<table>
 <tbody><tr>
  <th colspan="2" rowspan="2"></th>
  <th colspan="2">g++ 5.4.0</th>
  <th colspan="2">g++ 7.5.0</th>
  <th colspan="2">g++ 9.3.0</th>
  <th colspan="2">clang 11.0.3*</th>
  <th colspan="2">msvc 19.26</th>
  <th rowspan="2">Avg SpeedUp</th>
  <th rowspan="2">MAE</th>
  <th rowspan="2"></th>
 </tr>
 <tr>
  <th>Time(sec)</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
 </tr>
 <tr>
  <th rowspan="14">float</th>
  <th>simple(baseline)</th>
  <td>1.459 </td>
  <td>0%</td>
  <td>1.255 </td>
  <td>0%</td>
  <td>0.983 </td>
  <td>0%</td>
  <td>0.901 </td>
  <td>0%</td>
  <td>1.247 </td>
  <td>0%</td>
  <td>0%</td>
  <td>2.037</td>
  <th>simple(baseline)</th>
 </tr>
 <tr>
  <th>simple_double</th>
  <td>1.546 </td>
  <td>-6%</td>
  <td>1.648 </td>
  <td>-24%</td>
  <td>1.334 </td>
  <td>-26%</td>
  <td>1.281 </td>
  <td>-30%</td>
  <td>1.156 </td>
  <td>8%</td>
  <td>-11%</td>
  <td>-</td>
  <th>simple_double</th>
 </tr>
 <tr>
  <th>sse</th>
  <td>0.521 </td>
  <td>180%</td>
  <td>0.549 </td>
  <td>128%</td>
  <td>0.341 </td>
  <td>188%</td>
  <td>0.444 </td>
  <td>103%</td>
  <td>0.384 </td>
  <td>225%</td>
  <td>172%</td>
  <td>0.683</td>
  <th>sse</th>
 </tr>
 <tr>
  <th>kahan</th>
  <td>5.924 </td>
  <td>-75%</td>
  <td>4.789 </td>
  <td>-74%</td>
  <td>3.987 </td>
  <td>-75%</td>
  <td>3.497 </td>
  <td>-74%</td>
  <td>4.100 </td>
  <td>-70%</td>
  <td>-73%</td>
  <td>0.000</td>
  <th>kahan</th>
 </tr>
 <tr>
  <th>unroll4</th>
  <td>1.401 </td>
  <td>4%</td>
  <td>1.247 </td>
  <td>1%</td>
  <td>0.972 </td>
  <td>1%</td>
  <td>0.893 </td>
  <td>1%</td>
  <td>1.017 </td>
  <td>23%</td>
  <td>9%</td>
  <td>2.037</td>
  <th>unroll4</th>
 </tr>
 <tr>
  <th>unroll4_reorder1</th>
  <td>1.068 </td>
  <td>37%</td>
  <td>0.984 </td>
  <td>27%</td>
  <td>0.802 </td>
  <td>23%</td>
  <td>0.745 </td>
  <td>21%</td>
  <td>0.818 </td>
  <td>52%</td>
  <td>36%</td>
  <td>0.768</td>
  <th>unroll4_reorder1</th>
 </tr>
 <tr>
  <th>unroll4_shift</th>
  <td>0.896 </td>
  <td>63%</td>
  <td>0.514 </td>
  <td>144%</td>
  <td>0.919 </td>
  <td>7%</td>
  <td>0.545 </td>
  <td>65%</td>
  <td>0.917 </td>
  <td>36%</td>
  <td>57%</td>
  <td>0.683</td>
  <th>unroll4_shift</th>
 </tr>
 <tr>
  <th>unroll8</th>
  <td>1.431 </td>
  <td>2%</td>
  <td>1.240 </td>
  <td>1%</td>
  <td>1.042 </td>
  <td>-6%</td>
  <td>0.886 </td>
  <td>2%</td>
  <td>1.048 </td>
  <td>19%</td>
  <td>7%</td>
  <td>2.037</td>
  <th>unroll8</th>
 </tr>
 <tr>
  <th>unroll8_reorder1</th>
  <td>1.062 </td>
  <td>37%</td>
  <td>0.926 </td>
  <td>36%</td>
  <td>0.763 </td>
  <td>29%</td>
  <td>0.660 </td>
  <td>37%</td>
  <td>0.780 </td>
  <td>60%</td>
  <td>44%</td>
  <td>1.160</td>
  <th>unroll8_reorder1</th>
 </tr>
 <tr>
  <th>unroll8_reorder2</th>
  <td>1.249 </td>
  <td>17%</td>
  <td>0.849 </td>
  <td>48%</td>
  <td>0.645 </td>
  <td>52%</td>
  <td>0.634 </td>
  <td>42%</td>
  <td>0.692 </td>
  <td>80%</td>
  <td>55%</td>
  <td>0.833</td>
  <th>unroll8_reorder2</th>
 </tr>
 <tr>
  <th>unroll8_shift</th>
  <td>1.210 </td>
  <td>21%</td>
  <td>0.657 </td>
  <td>91%</td>
  <td>1.248 </td>
  <td>-21%</td>
  <td>0.591 </td>
  <td>52%</td>
  <td>1.294 </td>
  <td>-4%</td>
  <td>23%</td>
  <td>0.344</td>
  <th>unroll8_shift</th>
 </tr>
 <tr>
  <th>unroll16</th>
  <td>1.378 </td>
  <td>6%</td>
  <td>1.242 </td>
  <td>1%</td>
  <td>1.009 </td>
  <td>-3%</td>
  <td>0.897 </td>
  <td>0%</td>
  <td>1.036 </td>
  <td>20%</td>
  <td>8%</td>
  <td>2.037</td>
  <th>unroll16</th>
 </tr>
 <tr>
  <th>unroll16_reorder1</th>
  <td>0.880 </td>
  <td>66%</td>
  <td>0.891 </td>
  <td>41%</td>
  <td>0.715 </td>
  <td>37%</td>
  <td>0.701 </td>
  <td>29%</td>
  <td>0.728 </td>
  <td>71%</td>
  <td>52%</td>
  <td>1.198</td>
  <th>unroll16_reorder1</th>
 </tr>
 <tr>
  <th>unroll16_reorder2</th>
  <td>0.657 </td>
  <td>122%</td>
  <td>0.793 </td>
  <td>58%</td>
  <td>0.613 </td>
  <td>60%</td>
  <td>0.533 </td>
  <td>69%</td>
  <td>0.847 </td>
  <td>47%</td>
  <td>65%</td>
  <td>2.277</td>
  <th>unroll16_reorder2</th>
 </tr>
 <tr>
  <th rowspan="12">double</th>
  <th>simple(baseline)</th>
  <td>1.486 </td>
  <td>0%</td>
  <td>1.291 </td>
  <td>0%</td>
  <td>0.997 </td>
  <td>0%</td>
  <td>0.885 </td>
  <td>0%</td>
  <td>1.526 </td>
  <td>0%</td>
  <td>0%</td>
  <td>2.037</td>
  <th>simple(baseline)</th>
 </tr>
 <tr>
  <th>kahan</th>
  <td>5.563 </td>
  <td>-73%</td>
  <td>4.813 </td>
  <td>-73%</td>
  <td>4.079 </td>
  <td>-76%</td>
  <td>3.466 </td>
  <td>-74%</td>
  <td>4.267 </td>
  <td>-64%</td>
  <td>-70%</td>
  <td>-</td>
  <th>kahan</th>
 </tr>
 <tr>
  <th>unroll4</th>
  <td>1.478 </td>
  <td>1%</td>
  <td>1.248 </td>
  <td>3%</td>
  <td>1.032 </td>
  <td>-3%</td>
  <td>0.878 </td>
  <td>1%</td>
  <td>1.018 </td>
  <td>50%</td>
  <td>19%</td>
  <td>2.037</td>
  <th>unroll4</th>
 </tr>
 <tr>
  <th>unroll4_reorder1</th>
  <td>1.079 </td>
  <td>38%</td>
  <td>1.010 </td>
  <td>28%</td>
  <td>0.789 </td>
  <td>26%</td>
  <td>0.741 </td>
  <td>19%</td>
  <td>0.794 </td>
  <td>92%</td>
  <td>51%</td>
  <td>0.768</td>
  <th>unroll4_reorder1</th>
 </tr>
 <tr>
  <th>unroll4_shift</th>
  <td>0.927 </td>
  <td>60%</td>
  <td>0.544 </td>
  <td>138%</td>
  <td>0.919 </td>
  <td>8%</td>
  <td>0.468 </td>
  <td>89%</td>
  <td>0.967 </td>
  <td>58%</td>
  <td>70%</td>
  <td>0.683</td>
  <th>unroll4_shift</th>
 </tr>
 <tr>
  <th>unroll8</th>
  <td>1.549 </td>
  <td>-4%</td>
  <td>1.226 </td>
  <td>5%</td>
  <td>0.958 </td>
  <td>4%</td>
  <td>0.883 </td>
  <td>0%</td>
  <td>1.035 </td>
  <td>47%</td>
  <td>19%</td>
  <td>2.037</td>
  <th>unroll8</th>
 </tr>
 <tr>
  <th>unroll8_reorder1</th>
  <td>0.929 </td>
  <td>60%</td>
  <td>0.944 </td>
  <td>37%</td>
  <td>0.754 </td>
  <td>32%</td>
  <td>0.671 </td>
  <td>32%</td>
  <td>0.765 </td>
  <td>100%</td>
  <td>61%</td>
  <td>1.160</td>
  <th>unroll8_reorder1</th>
 </tr>
 <tr>
  <th>unroll8_reorder2</th>
  <td>0.808 </td>
  <td>84%</td>
  <td>0.831 </td>
  <td>55%</td>
  <td>0.619 </td>
  <td>61%</td>
  <td>0.616 </td>
  <td>44%</td>
  <td>0.673 </td>
  <td>127%</td>
  <td>83%</td>
  <td>0.833</td>
  <th>unroll8_reorder2</th>
 </tr>
 <tr>
  <th>unroll8_shift</th>
  <td>1.240 </td>
  <td>20%</td>
  <td>0.648 </td>
  <td>99%</td>
  <td>1.208 </td>
  <td>-18%</td>
  <td>0.606 </td>
  <td>46%</td>
  <td>1.269 </td>
  <td>20%</td>
  <td>32%</td>
  <td>0.344</td>
  <th>unroll8_shift</th>
 </tr>
 <tr>
  <th>unroll16</th>
  <td>1.431 </td>
  <td>4%</td>
  <td>1.247 </td>
  <td>4%</td>
  <td>1.015 </td>
  <td>-2%</td>
  <td>0.904 </td>
  <td>-2%</td>
  <td>1.019 </td>
  <td>50%</td>
  <td>19%</td>
  <td>2.037</td>
  <th>unroll16</th>
 </tr>
 <tr>
  <th>unroll16_reorder1</th>
  <td>0.861 </td>
  <td>73%</td>
  <td>0.907 </td>
  <td>42%</td>
  <td>0.690 </td>
  <td>44%</td>
  <td>0.622 </td>
  <td>42%</td>
  <td>0.727 </td>
  <td>110%</td>
  <td>72%</td>
  <td>1.198</td>
  <th>unroll16_reorder1</th>
 </tr>
 <tr>
  <th>unroll16_reorder2</th>
  <td>0.621 </td>
  <td>139%</td>
  <td>0.812 </td>
  <td>59%</td>
  <td>0.619 </td>
  <td>61%</td>
  <td>0.509 </td>
  <td>74%</td>
  <td>0.802 </td>
  <td>90%</td>
  <td>85%</td>
  <td>2.277</td>
  <th>unroll16_reorder2</th>
 </tr></tbody></table>
 
 ## Compiled with AVX option
 
<table>
 <tbody><tr>
  <th colspan="2" rowspan="2"></th>
  <th colspan="2">g++ 5.4.0</th>
  <th colspan="2">g++ 7.5.0</th>
  <th colspan="2">g++ 9.3.0</th>
  <th colspan="2">clang 11.0.3*</th>
  <th colspan="2">msvc 19.26</th>
  <th rowspan="2">Avg SpeedUp</th>
  <th rowspan="2">MAE</th>
  <th rowspan="2"></th>
 </tr>
 <tr>
  <th>Time(sec)</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
  <th>Time</th>
  <th>SpeedUp</th>
 </tr>
 <tr>
  <th rowspan="15">float</th>
  <th>simple(baseline)</th>
  <td>1.245 </td>
  <td>0%</td>
  <td>1.071 </td>
  <td>0%</td>
  <td>0.995 </td>
  <td>0%</td>
  <td>0.862 </td>
  <td>0%</td>
  <td>1.243 </td>
  <td>0%</td>
  <td>0%</td>
  <td>2.037</td>
  <th>simple(baseline)</th>
 </tr>
 <tr>
  <th>simple_double</th>
  <td>1.614 </td>
  <td>-23%</td>
  <td>1.515 </td>
  <td>-29%</td>
  <td>1.263 </td>
  <td>-21%</td>
  <td>1.173 </td>
  <td>-27%</td>
  <td>1.269 </td>
  <td>-2%</td>
  <td>-17%</td>
  <td>-</td>
  <th>simple_double</th>
 </tr>
 <tr>
  <th>avx</th>
  <td>0.514 </td>
  <td>142%</td>
  <td>0.502 </td>
  <td>113%</td>
  <td>0.492 </td>
  <td>102%</td>
  <td>0.481 </td>
  <td>79%</td>
  <td>0.577 </td>
  <td>116%</td>
  <td>108%</td>
  <td>0.344</td>
  <th>avx</th>
 </tr>
 <tr>
  <th>sse</th>
  <td>0.394 </td>
  <td>216%</td>
  <td>0.358 </td>
  <td>199%</td>
  <td>0.345 </td>
  <td>189%</td>
  <td>0.405 </td>
  <td>113%</td>
  <td>0.504 </td>
  <td>147%</td>
  <td>159%</td>
  <td>0.683</td>
  <th>sse</th>
 </tr>
 <tr>
  <th>kahan</th>
  <td>4.825 </td>
  <td>-74%</td>
  <td>4.246 </td>
  <td>-75%</td>
  <td>3.860 </td>
  <td>-74%</td>
  <td>3.406 </td>
  <td>-75%</td>
  <td>4.069 </td>
  <td>-69%</td>
  <td>-73%</td>
  <td>0.000</td>
  <th>kahan</th>
 </tr>
 <tr>
  <th>unroll4</th>
  <td>1.179 </td>
  <td>6%</td>
  <td>1.213 </td>
  <td>-12%</td>
  <td>0.992 </td>
  <td>0%</td>
  <td>0.861 </td>
  <td>0%</td>
  <td>1.249 </td>
  <td>0%</td>
  <td>-1%</td>
  <td>2.037</td>
  <th>unroll4</th>
 </tr>
 <tr>
  <th>unroll4_reorder1</th>
  <td>0.988 </td>
  <td>26%</td>
  <td>0.871 </td>
  <td>23%</td>
  <td>0.813 </td>
  <td>22%</td>
  <td>0.727 </td>
  <td>19%</td>
  <td>0.972 </td>
  <td>28%</td>
  <td>24%</td>
  <td>0.768</td>
  <th>unroll4_reorder1</th>
 </tr>
 <tr>
  <th>unroll4_shift</th>
  <td>0.679 </td>
  <td>84%</td>
  <td>0.910 </td>
  <td>18%</td>
  <td>0.937 </td>
  <td>6%</td>
  <td>0.570 </td>
  <td>51%</td>
  <td>0.534 </td>
  <td>133%</td>
  <td>76%</td>
  <td>0.683</td>
  <th>unroll4_shift</th>
 </tr>
 <tr>
  <th>unroll8</th>
  <td>1.229 </td>
  <td>1%</td>
  <td>1.049 </td>
  <td>2%</td>
  <td>0.949 </td>
  <td>5%</td>
  <td>0.862 </td>
  <td>0%</td>
  <td>1.027 </td>
  <td>21%</td>
  <td>9%</td>
  <td>2.037</td>
  <th>unroll8</th>
 </tr>
 <tr>
  <th>unroll8_reorder1</th>
  <td>1.026 </td>
  <td>21%</td>
  <td>0.753 </td>
  <td>42%</td>
  <td>0.734 </td>
  <td>36%</td>
  <td>0.630 </td>
  <td>37%</td>
  <td>0.792 </td>
  <td>57%</td>
  <td>43%</td>
  <td>1.160</td>
  <th>unroll8_reorder1</th>
 </tr>
 <tr>
  <th>unroll8_reorder2</th>
  <td>0.758 </td>
  <td>64%</td>
  <td>0.673 </td>
  <td>59%</td>
  <td>0.627 </td>
  <td>59%</td>
  <td>0.570 </td>
  <td>51%</td>
  <td>0.715 </td>
  <td>74%</td>
  <td>63%</td>
  <td>0.833</td>
  <th>unroll8_reorder2</th>
 </tr>
 <tr>
  <th>unroll8_shift</th>
  <td>0.756 </td>
  <td>65%</td>
  <td>1.356 </td>
  <td>-21%</td>
  <td>1.246 </td>
  <td>-20%</td>
  <td>0.776 </td>
  <td>11%</td>
  <td>0.631 </td>
  <td>97%</td>
  <td>42%</td>
  <td>0.344</td>
  <th>unroll8_shift</th>
 </tr>
 <tr>
  <th>unroll16</th>
  <td>1.171 </td>
  <td>6%</td>
  <td>1.009 </td>
  <td>6%</td>
  <td>1.003 </td>
  <td>-1%</td>
  <td>0.876 </td>
  <td>-2%</td>
  <td>1.074 </td>
  <td>16%</td>
  <td>7%</td>
  <td>2.037</td>
  <th>unroll16</th>
 </tr>
 <tr>
  <th>unroll16_reorder1</th>
  <td>0.829 </td>
  <td>50%</td>
  <td>0.769 </td>
  <td>39%</td>
  <td>0.680 </td>
  <td>46%</td>
  <td>0.571 </td>
  <td>51%</td>
  <td>0.773 </td>
  <td>61%</td>
  <td>53%</td>
  <td>1.198</td>
  <th>unroll16_reorder1</th>
 </tr>
 <tr>
  <th>unroll16_reorder2</th>
  <td>0.726 </td>
  <td>71%</td>
  <td>0.626 </td>
  <td>71%</td>
  <td>0.569 </td>
  <td>75%</td>
  <td>0.494 </td>
  <td>75%</td>
  <td>0.943 </td>
  <td>32%</td>
  <td>58%</td>
  <td>2.277</td>
  <th>unroll16_reorder2</th>
 </tr>
 <tr>
  <th rowspan="12">double</th>
  <th>simple(baseline)</th>
  <td>1.214 </td>
  <td>0%</td>
  <td>1.066 </td>
  <td>0%</td>
  <td>0.952 </td>
  <td>0%</td>
  <td>0.875 </td>
  <td>0%</td>
  <td>1.537 </td>
  <td>0%</td>
  <td>0%</td>
  <td>2.037</td>
  <th>simple(baseline)</th>
 </tr>
 <tr>
  <th>kahan</th>
  <td>4.790 </td>
  <td>-75%</td>
  <td>4.175 </td>
  <td>-74%</td>
  <td>3.821 </td>
  <td>-75%</td>
  <td>3.431 </td>
  <td>-75%</td>
  <td>3.986 </td>
  <td>-61%</td>
  <td>-70%</td>
  <td>-</td>
  <th>kahan</th>
 </tr>
 <tr>
  <th>unroll4</th>
  <td>1.152 </td>
  <td>5%</td>
  <td>1.032 </td>
  <td>3%</td>
  <td>0.933 </td>
  <td>2%</td>
  <td>0.866 </td>
  <td>1%</td>
  <td>1.243 </td>
  <td>24%</td>
  <td>10%</td>
  <td>2.037</td>
  <th>unroll4</th>
 </tr>
 <tr>
  <th>unroll4_reorder1</th>
  <td>0.975 </td>
  <td>25%</td>
  <td>0.890 </td>
  <td>20%</td>
  <td>0.810 </td>
  <td>18%</td>
  <td>0.732 </td>
  <td>19%</td>
  <td>0.959 </td>
  <td>60%</td>
  <td>35%</td>
  <td>0.768</td>
  <th>unroll4_reorder1</th>
 </tr>
 <tr>
  <th>unroll4_shift</th>
  <td>0.683 </td>
  <td>78%</td>
  <td>0.950 </td>
  <td>12%</td>
  <td>0.919 </td>
  <td>4%</td>
  <td>0.567 </td>
  <td>54%</td>
  <td>0.523 </td>
  <td>194%</td>
  <td>98%</td>
  <td>0.683</td>
  <th>unroll4_shift</th>
 </tr>
 <tr>
  <th>unroll8</th>
  <td>1.194 </td>
  <td>2%</td>
  <td>1.063 </td>
  <td>0%</td>
  <td>0.965 </td>
  <td>-1%</td>
  <td>0.870 </td>
  <td>1%</td>
  <td>1.034 </td>
  <td>49%</td>
  <td>18%</td>
  <td>2.037</td>
  <th>unroll8</th>
 </tr>
 <tr>
  <th>unroll8_reorder1</th>
  <td>0.876 </td>
  <td>39%</td>
  <td>0.761 </td>
  <td>40%</td>
  <td>0.715 </td>
  <td>33%</td>
  <td>0.639 </td>
  <td>37%</td>
  <td>0.838 </td>
  <td>83%</td>
  <td>54%</td>
  <td>1.160</td>
  <th>unroll8_reorder1</th>
 </tr>
 <tr>
  <th>unroll8_reorder2</th>
  <td>0.791 </td>
  <td>54%</td>
  <td>0.665 </td>
  <td>60%</td>
  <td>0.642 </td>
  <td>48%</td>
  <td>0.576 </td>
  <td>52%</td>
  <td>0.721 </td>
  <td>113%</td>
  <td>76%</td>
  <td>0.833</td>
  <th>unroll8_reorder2</th>
 </tr>
 <tr>
  <th>unroll8_shift</th>
  <td>0.750 </td>
  <td>62%</td>
  <td>1.237 </td>
  <td>-14%</td>
  <td>1.259 </td>
  <td>-24%</td>
  <td>0.763 </td>
  <td>15%</td>
  <td>0.624 </td>
  <td>146%</td>
  <td>61%</td>
  <td>0.344</td>
  <th>unroll8_shift</th>
 </tr>
 <tr>
  <th>unroll16</th>
  <td>1.158 </td>
  <td>5%</td>
  <td>1.031 </td>
  <td>3%</td>
  <td>0.960 </td>
  <td>-1%</td>
  <td>0.874 </td>
  <td>0%</td>
  <td>1.034 </td>
  <td>49%</td>
  <td>19%</td>
  <td>2.037</td>
  <th>unroll16</th>
 </tr>
 <tr>
  <th>unroll16_reorder1</th>
  <td>0.825 </td>
  <td>47%</td>
  <td>0.750 </td>
  <td>42%</td>
  <td>0.705 </td>
  <td>35%</td>
  <td>0.609 </td>
  <td>44%</td>
  <td>0.747 </td>
  <td>106%</td>
  <td>66%</td>
  <td>1.198</td>
  <th>unroll16_reorder1</th>
 </tr>
 <tr>
  <th>unroll16_reorder2</th>
  <td>0.752 </td>
  <td>61%</td>
  <td>0.636 </td>
  <td>68%</td>
  <td>0.587 </td>
  <td>62%</td>
  <td>0.492 </td>
  <td>78%</td>
  <td>0.958 </td>
  <td>61%</td>
  <td>66%</td>
  <td>2.277</td>
  <th>unroll16_reorder2</th>
 </tr></tbody></table>
