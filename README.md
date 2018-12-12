# Advent of Code | C++

To compile just run `make`.

## Usage

```
aoc18 [-b] [-i filename] day
```

###Flags
* `-b` Toggles benchmarking. Final result will include running time
* `-i` Solutions will read given input file
* `day` An integer in the range 1-25

If no input file is given, the executable will default to reading stdin.

### Examples

* `aoc18 -bi inputs/input_3.txt 3`<br>
  will run day 3 with input file `inputs/input_3.txt`. will also run benchmarking.


* `aoc18 4 < inputs/input_4.txt`<br>
  will run 4 day from stdin (which is the contents of `inputs/input_4.txt`)
  
## LICENSE

Copyright &copy; 2018 Phillip Raffnsøe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
