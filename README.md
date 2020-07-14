# The Check Digit Algorithm for NTU Matriculation Numbers

## Quick Navigation

* [Matric Number Check Digit Validator](https://zhongruoyu.github.io/ntu-matric-number/)
* [Reverse Engineering Program (in C)](https://github.com/ZhongRuoyu/ntu-matric-number/blob/master/calculation/ntu_matric.c)
* [Blog Post](https://zhongruoyu.github.io/projects/2020-07/ntu-matric-number/)

## The Modulo 11 Algorithm

It is reasonable to guess that the check digit algorithm for our matric numbers shares the same pattern with that of the NRIC number / FIN, based on the following facts:

* The pattern of NTU matric numbers (e.g. `U2024197H`) is similar to that of the Singapore NRIC number / FIN[^1];
* On observing dozens of data, it can be noticed that the check digit ranges from `A` to `L` excluding `I`, and that is a total of 11 possibilities. The case is the same for the NRIC number / FIN [^2].

That is the modulo 11 algorithm. It is a very common algorithm used to calculate check digits.

Taking the above-mentioned matric number (`U2024197H`) as an example, the procedure for calculating the check digit using the modulo 11 algorithm is as follows:

1. Put the 11 possible check digits in an ordered array `ALPHA[11]`: `ALPHA[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L'}`.
2. Take out the digits in the matric number, namely `d0` to `d6`: `{2, 0, 2, 4, 1, 9, 7}`.
3. Multiply each digit with its corresponding weighting factor (`w0` to `w6`, discussed below), and add them together: `S = d0*w0 + d1*w1 + d2*w2 + d3*w3 + d4*w4 + d5*w5 + d6*w6`.
4. Add an offset number `a`, which may be any integer from 0 to 10, to produce the offset sum `S_o`: `S_o = S + a`.
5. Divide the offset sum `S_o` by 11, and get the remainder `R`: `R = S_o % 11`.
6. The check digit is just `ALPHA[R]`.

## The Weighting Coefficients and the Offset Number

[Reverse engineering](https://github.com/ZhongRuoyu/ntu-matric-number/blob/master/calculation/ntu_matric.c)[^3] has shown that the matric numbers are indeed using the modulo 11 algorithm.

Due to the limitations of sample data, only matric numbers starting with '`U`' or '`B`' are studied.

* For matric numbers starting with '`U`', obtained before (and including) 2016[^4]:
  |`w0`|`w1`|`w2`|`w3`|`w4`|`w5`|`w6`|`a`|
  |----|----|----|----|----|----|----|---|
  |10  |7   |4   |3   |2   |9   |8   |0  |
* Due to the limitations of the sample data, matric numbers starting with '`U`' and obtained in 2017 have not been studied. The data set should be the same as either above or below.
* For matric numbers starting with '`U`', obtained after (and including) 2018:
  |`w0`|`w1`|`w2`|`w3`|`w4`|`w5`|`w6`|`a`|
  |----|----|----|----|----|----|----|---|
  |6   |7   |4   |3   |8   |9   |2   |4  |
* For bridging numbers (matric numbers starting with '`B`'):
  |`w0`|`w1`|`w2`|`w3`|`w4`|`w5`|`w6`|`a`|
  |----|----|----|----|----|----|----|---|
  |10  |7   |4   |3   |2   |9   |8   |9  |

## About

For more information about the discovery, please visit [my blog page](https://zhongruoyu.github.io/projects/2020-07/ntu-matric-number/).

## License & Disclaimer

This repository (ZhongRuoyu/ntu-matric-number) is licensed under the [MIT License](https://github.com/ZhongRuoyu/ntu-matric-number/blob/master/LICENSE).

The check digit algorithm is based on a study on a number of NTU matriculation numbers, and has been verified with a number of real cases. However, the results are not guaranteed to be accurate. Since the algorithm only calculates the check digit of matriculation numbers, it is also not guaranteed that the numbers that pass the validation actually exist. Please use it for reference only.

The above-mentioned algorithm, if exists, belongs to Nanyang Technological University, Singapore.

## Acknowledgement

I would like to express my sincere appreciation to those who have provided their matric numbers to me. Without their help, this could not have been possible.

## Footnotes

[^1]: [National Registration Identity Card - Wikipedia](https://en.wikipedia.org/wiki/National_Registration_Identity_Card)

[^2]: [Fun with numbers](http://www.ngiam.net/NRIC/)

[^3]: For privacy concerns, the actual data that I used have been removed, and only sample data is displayed. Nevertheless, the sample data provided in the source code can also lead to that only result. The example `U2024197H` used here is also a sample; it is not intentionally linked to anyone.

[^4]: [Daniel D. Zhang - The Secret behind NTU Matriculation Numbers](https://github.com/idf/idf.github.io-deprecated/blob/master/_posts/2014-03-17-the-secret-behind-ntu-matriculation-numbers.md)