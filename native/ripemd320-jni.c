#include <stdint.h>
#include <jni.h>


extern void ripemd320_compress_block(const jbyte *block, uint32_t state[10]);


/*
 * Class:     nayuki_nativehash_Ripemd320
 * Method:    compress
 * Signature: ([I[BII)Z
 */
JNIEXPORT jboolean JNICALL Java_nayuki_nativehash_Ripemd320_compress(JNIEnv *env, jclass thisClass, jintArray stateArray, jbyteArray msg, jint off, jint len) {
	JNIEnv theEnv = *env;
	
	// Get state array and convert to uint32_t
	jint *stateJava = theEnv->GetIntArrayElements(env, stateArray, NULL);
	if (stateJava == NULL)
		return 0;
	unsigned int i;
	uint32_t state[10];
	for (i = 0; i < 10; i++)
		state[i] = (uint32_t)stateJava[i];
	
	// Iterate over each block in msg. Requires len to be a multiple of 64
	jbyte *block = theEnv->GetPrimitiveArrayCritical(env, msg, NULL);
	if (block == NULL)
		return 0;
	size_t newoff;
	size_t newlen = len;
	for (newoff = 0; newoff < newlen; newoff += 64)
		ripemd320_compress_block(block + off + newoff, state);
	theEnv->ReleasePrimitiveArrayCritical(env, msg, block, JNI_ABORT);
	
	// Convert state array to jint and clean up
	for (i = 0; i < 10; i++)
		stateJava[i] = (jint)state[i];
	theEnv->ReleaseIntArrayElements(env, stateArray, stateJava, 0);
	return 1;
}