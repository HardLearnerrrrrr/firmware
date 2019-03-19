let speed = 0.5;
function setup() {
	createCanvas(window.innerWidth, window.innerHeight);
	background(51);
	angleMode(DEGREES);

/* Branching rules*/
	rules = [];
// A
	var a = new LSystem('F', random(15,60), 75, 0.5, 5);
	a.color = color(255, 243, 217);
	a.addRule('F', 'F[+F]F[-F]F');
// B
	var b = new LSystem('F', random(15,40), 290, 0.5, 5);
	b.color = color(198, 228, 255);
	b.addRule('F', 'F[+F]F[-F][F]');
//C
	var c = new LSystem('F', random(15,30), 150, 0.5, 4);
	c.color = color(194, 207, 207);
	c.addRule('F', 'FF-[-F+F+F]+[+F-F-F]');
//D
	var d = new LSystem('X', random(15,30), 300, 0.5, 7);
	d.color = color(125, 138, 102);
	d.addRule('X', 'F[+X]F[-X]+X');
	d.addRule('F', 'FF');
// E
	var e = new LSystem('X', random(20,35), 295, 0.5, 7);
	e.color = color(219, 255, 175);
	e.addRule('X', 'F[+X][-X]FX');
	e.addRule('F', 'FF');
// F
	var f = new LSystem('X', random(15,30), 225, 0.5, 6);
	f.color = color(255, 212, 206);
	f.addRule('X', 'F-[[X]+X]+F[+FX]-X');
	f.addRule('F', 'FF');
	rules.push(a, b, c, d, e, f);
	preset= Math.floor(random(0,6))
	//preset = 5;
	system = rules[preset];
	system.run();

}
function LSystem(axiom, angle, lineLength, lengthMod, iterations) {
	this.axiom = axiom;
	this.angle = parseFloat(angle);
	this._lineLength = lineLength;
	this.lineLength = this._lineLength;
	this.lengthMod = lengthMod;
	this.iterations = iterations;
	this.rules = {};
	this.instructions = {};
	this.color = color(255, 243, 217)
	this.texture = createGraphics(window.innerWidth, window.innerHeight);
	this.addInstruction('F', function() {
	  line(0, 0, 0, -this.lineLength);
	  translate(0, -this.lineLength);
	});
	this.addInstruction('+', function() {
	  rotate(-this.angle);
	});
	this.addInstruction('X',function(){
		line(0, 0, -this.lineLength, 0);
	  translate(0, -this.lineLength);
	});
	this.addInstruction('-', function() {
	  rotate(this.angle);
	});
	this.addInstruction('[', function() {
	  push();
	});
	this.addInstruction(']', function() {
	  pop();
	});
	this.sentence = this.axiom;
  
  }
  LSystem.prototype = {
		addRule: function(input, output, chance) {
	  	if (!chance) {
			chance = 1.0;
	  	}
	  	this.rules[input] = {
			transform: output,
			chance: chance
	  	};
		},
	addInstruction: function(char, callback, context) {
	  if (!context) {
			context = this;
	  }
	  this.instructions[char] = callback.bind(context);
	},
	generate: function() {
	  	var s = '';
	  	var chars = this.getTokens();
	  	chars.forEach(function(c) {
			if (this.rules.hasOwnProperty(c)) {
		  var rule = this.rules[c];
		  var r = random();
		  if (r <= rule.chance) {
			s += rule.transform;
		  }
		} else {
		  s += c;
		}
	  }, this)
	  this.sentence = s;
	  this.lineLength *= this.lengthMod;
	},
	render: function() {
	},
	draw: function() {
	  	stroke(this.color);
	  	var chars = this.getTokens();
	  	chars.forEach(function(c) {
			if (this.instructions.hasOwnProperty(c)) { 
		  	this.instructions[c]();
		}
	  }, this);
	},
	getTokens: function() {
		return this.sentence.match(/./g);
		},
		run() {
	  	this.sentence = this.axiom;
	  	this.lineLength = this._lineLength;
	  	for (var i = 0; i < this.iterations; i++) {
			this.generate();
	  }
		}
  }
  
  // global variables
		var system, rules, preset;
  	preset = 0;
  	selected = 0;
  // initialize variables and display 

  function update() {}
  
  // draw function is used to render display objects
  function draw() {
	// call the update function
	update();
	background(55);
	strokeWeight(1.2);
	noFill();
	push();
//	translate(width * 0.2, height);
	system.draw();
	pop();
  }