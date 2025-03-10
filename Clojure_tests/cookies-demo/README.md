# cookies-demo

Demonstration of cookies and middleware for a ring/compojure app

## Usage

```
lein run
```

And visit
- http://localhost:8989/set-cookie-raw
- http://localhost:8989/set-cookies-middleware
- http://localhost:8989/show-cookies-raw
- http://localhost:8989/show-cookies-middleware
in your browser

## Code

The code is in the file [src/cookies-demo/core.clj](src/cookies-demo/core.clj)
and is pretty well commented.

## Notes

See [Notes](Notes.org) that gives a high level explanation of two methods of
setting in responses and reading cookies in requests.

## License

Copyright © 2025 Philippe Carphin

This program and the accompanying materials are made available under the
terms of the Eclipse Public License 2.0 which is available at
http://www.eclipse.org/legal/epl-2.0.

This Source Code may also be made available under the following Secondary
Licenses when the conditions for such availability set forth in the Eclipse
Public License, v. 2.0 are satisfied: GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or (at your
option) any later version, with the GNU Classpath Exception which is available
at https://www.gnu.org/software/classpath/license.html.
