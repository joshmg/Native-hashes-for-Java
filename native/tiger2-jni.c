#include <stdint.h>
#include <jni.h>


extern void tiger2_compress_block(const jbyte *block, uint64_t state[3]);


/*
 * Class:     nayuki_nativehash_Tiger2
 * Method:    compress
 * Signature: ([J[BII)Z
 */
JNIEXPORT jboolean JNICALL Java_nayuki_nativehash_Tiger2_compress(JNIEnv *env, jclass thisClass, jlongArray stateArray, jbyteArray msg, jint off, jint len) {
	JNIEnv theEnv = *env;
	
	// Get state array and convert to uint64_t
	jlong *stateJava = theEnv->GetLongArrayElements(env, stateArray, NULL);
	if (stateJava == NULL)
		return 0;
	unsigned int i;
	uint64_t state[3];
	for (i = 0; i < 3; i++)
		state[i] = (uint64_t)stateJava[i];
	
	// Iterate over each block in msg. Requires len to be a multiple of 64
	jbyte *block = theEnv->GetPrimitiveArrayCritical(env, msg, NULL);
	if (block == NULL)
		return 0;
	size_t newoff;
	size_t newlen = len;
	for (newoff = 0; newoff < newlen; newoff += 64)
		tiger2_compress_block(block + off + newoff, state);
	theEnv->ReleasePrimitiveArrayCritical(env, msg, block, JNI_ABORT);
	
	// Convert state array to jlong and clean up
	for (i = 0; i < 3; i++)
		stateJava[i] = (jlong)state[i];
	theEnv->ReleaseLongArrayElements(env, stateArray, stateJava, 0);
	return 1;
}
