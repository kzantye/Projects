package genericCheckpointing.xmlStoreRestore;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import genericCheckpointing.util.SerializableObject;

public interface SerStrategy {
	   void processInput(Object sObject,BufferedWriter writer) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException;

	SerializableObject processInput(BufferedReader writer) throws IOException, ClassNotFoundException, InstantiationException, IllegalAccessException, NumberFormatException, IllegalArgumentException, InvocationTargetException;

	}
