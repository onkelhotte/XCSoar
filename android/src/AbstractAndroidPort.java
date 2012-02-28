/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

package org.xcsoar;

import java.io.InputStream;
import java.io.OutputStream;

/**
 * Abstract base class to aid the real implementations (Bluetooth,
 * IOIO).
 */
abstract class AbstractAndroidPort implements AndroidPort {
  private InputThread input;
  private OutputThread output;

  private synchronized InputThread stealInput() {
    InputThread i = input;
    input = null;
    return i;
  }

  private synchronized OutputThread stealOutput() {
    OutputThread o = output;
    output = null;
    return o;
  }

  protected synchronized void set(InputStream _input, OutputStream _output) {
    input = new InputThread(_input);
    output = new OutputThread(_output);
    output.setTimeout(5000);
  }

  public void close() {
    InputThread i = stealInput();
    if (i != null)
      i.close();

    OutputThread o = stealOutput();
    if (o != null)
      o.close();
  }

  public final void flush() {
    InputThread i = input;
    if (i != null)
      i.flush();
  }

  public final void setReadTimeout(int timeout) {
    InputThread i = input;
    if (i != null)
      i.setTimeout(timeout);
  }

  public final int waitRead(int timeout) {
    InputThread i = input;
    return i != null
      ? i.waitRead(timeout)
      : 2; /* WaitResult::FAILED */
  }

  public final int read() {
    InputThread i = input;
    return i != null
      ? i.read()
      : -1;
  }

  public final boolean write(byte ch) {
    OutputThread o = output;
    return o != null && o.write(ch);
  }
}