# DSignal library
Travis CI: [![Build Status](https://travis-ci.com/Darek7D/DSignal.svg?branch=master)](https://travis-ci.com/Darek7D/DSignal)

The small simple signal pipeline library.

## Version info
Current version: 0.1.0 - early stage of development, no stable version currently.

## Examples

### SignalProcessors
Signal processor is the "smallest" computing unit in DSignal library. It behaves like a queue. You can push a data to it, and on every push, it make some processing storing it in the output buffer.
The library has some predefined signal processors such like: Min, Max, FilterIIR, FilterFIR, Decimator, RMS, Additionner, Multiplier....

```// Create SignalProcessor that's computes maximum value in the buffer.
Max m;

// Push some values
m.push(10); 
m.push(50);
m.push(60);
m.push(30);
m.push(40);
m.push(10);

// Get values from buffer
std::cout << m.pop() << std::endl; // outputs 10
std::cout << m.pop() << std::endl; // outputs 50
std::cout << m.pop() << std::endl; // outputs 60
std::cout << m.pop() << std::endl; // outputs 60
std::cout << m.pop() << std::endl; // outputs 60
std::cout << m.pop() << std::endl; // outputs 60
```

### SignalVector
The SignalVector is nothing but a multichannel version of SignalProcessor. It takes a Sample as an input and push every channel of Sample to separate SignalProcessor. It doesn't collect any data itself. Every pushed values are forwarded to provided SignalProcessor.

```
// Create 4-channel SignalVector with SignalProcessorBuffered as a computing unit.
SignalVector sig(4, SignalProcessorBuffered());

// Create a 4-channel sample with random values.
Sample s(4);
s.set(0, 10);
s.set(1, 11);
s.set(2, 12);
s.set(3, 13);

// Push it to the SignalVector.
sig.push(s);
sig.push(s);

// Get values
// first sample
Sample s1 = sig.pop();
std::cout << s1.get(0) << std::endl; // outputs 10
std::cout << s1.get(1) << std::endl; // outputs 11
std::cout << s1.get(2) << std::endl; // outputs 12
std::cout << s1.get(3) << std::endl; // outputs 13

// second sample
Sample s2 = sig.pop();
std::cout << s2.get(0) << std::endl; // outputs 10
std::cout << s2.get(1) << std::endl; // outputs 11
std::cout << s2.get(2) << std::endl; // outputs 12
std::cout << s2.get(3) << std::endl; // outputs 13
```

### SignalFlow
The SignalFlow allows to design the signal flow process before processing anything, by using operator>> and split() method. The designed signal flow process is stored in SignalFlowSession and processed when SignalFlowSession::process() method is used.

```
// Create session
SignalFlowSession s;

// Create signal flow elements
SignalFlow sig1(s, 4, SignalProcessorBuffered(), "Signal 1");
SignalFlow sig2(s, 4, SignalProcessorBuffered(), "Signal 2");

// Declare inputs/outputs
s.setInput(sig1);
s.setOutput(sig2);

// Design signal flow process
sig1 >> sig2;

// Create sample and push it to session
Sample sample(4);
s.input()->push(sample);

// Process all sample through signal processors.
s.process();

// Pop output sample
Sample out = s.output()->pop(); 
```

The visualisation of other sample session:
https://raw.githubusercontent.com/Darek7D/DSignal/master/doc/signalflow_example.svg
 
## Building
```sh
git clone https://github.com/Darek7D/DSignal.git
mkdir DSignal/build
cd DSignal/build
cmake ..
make -j12
make install
```