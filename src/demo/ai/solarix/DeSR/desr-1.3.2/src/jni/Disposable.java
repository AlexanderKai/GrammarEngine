/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package jni;

public class Disposable {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected Disposable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Disposable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        desrJNI.delete_Disposable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void Dispose() {
    desrJNI.Disposable_Dispose(swigCPtr, this);
  }

  public Disposable() {
    this(desrJNI.new_Disposable(), true);
  }

}
