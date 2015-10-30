# Simplex Framework

[![Build Status](https://travis-ci.org/franciscotufro/simplex-framework.svg?branch=master)](https://travis-ci.org/franciscotufro/simplex-framework)
[![Coverage Status](https://coveralls.io/repos/franciscotufro/simplex-framework/badge.svg?branch=master&service=github)](https://coveralls.io/github/franciscotufro/simplex-framework?branch=master)

Simplex Framework wants to be a set of reusable libraries and a standarized way to work with them to aid game development.

## Philosophy
In the quest for expression, art and the sense of authorship, I crashed into a wall when working with generalistic game engines like Unity or UE4.
The main problem is that those engines force you to work in a way that is not always comfortable for me.

When thinking about it, I noticed that the main issue is not Unity or Unreal, is the idea of creating generalistic game engines with APIs that tend to
solve as many problems as possible (even if you don't have them), and thus, generating tons of overhead. Don't get me wrong, those are incredible
pieces of software, and have helped zillions of wanabes to create games with ease, but my feeling is that they tend to create lazy developers that
don't learn much, because they can buy some asset that does the job for them.  This is a problem for me, I don't want to be that kind of programmer,
so, I'm not sure where this is going to go, but I'm starting my quest to regain authorship and learn more with this framework.

## Testing
I'm a TDD fan, and I've always been frustrated that Unity made it so difficult to test your code. Now that I'm building a framework, it's made using TDD
in mind, so the game should be easily testable.

For C++ code I'm using GoogleTest.

## Why is this a Framework and not an Engine
Because I believe that the engine that moves a game should be game-specific, and not generalistic. A Framework on the other hand provides a set of
general tools that can be used to aid in the creation of game engines.

## Free and Open Source
The Framework is free of charge and Open Source and release under MIT License. For details read LICENSE.
