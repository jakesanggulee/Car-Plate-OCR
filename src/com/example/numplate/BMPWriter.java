
package com.example.numplate;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import android.graphics.Bitmap;
import android.util.Log;

public class BMPWriter {

    private static final int BWOT = 4;
    private static final int BPP = 3;
    
    
    private static byte[] Int_writer(int value) throws IOException {
        byte[] b = new byte[4];

        b[0] = (byte)(value & 0x000000FF);
        b[1] = (byte)((value & 0x0000FF00) >> 8);
        b[2] = (byte)((value & 0x00FF0000) >> 16);
        b[3] = (byte)((value & 0xFF000000) >> 24);

        return b;
    }

 
    private static byte[] Short_writer(short value) throws IOException {
        byte[] b = new byte[2];

        b[0] = (byte)(value & 0x00FF);
        b[1] = (byte)((value & 0xFF00) >> 8);

        return b;
    }
    

    public static boolean save(Bitmap original_BMP, String filePath) throws IOException {
        if(original_BMP == null || filePath == null){
            return false;
        }

        boolean isSuc = true;

        //image size
        int width = original_BMP.getWidth();
        int height = original_BMP.getHeight();

        byte[] headerBPP = null;
        boolean additional_Dummy = false;
        int rw_bytes = BPP * width;
        if(rw_bytes%BWOT>0){
            additional_Dummy=true;
            headerBPP = new byte[(BWOT-(rw_bytes%BWOT))];
            for(int i = 0; i < headerBPP.length; i++){
                headerBPP[i] = (byte)0xFF;
            }
        }

        int[] pixels = new int[width * height];
        int imageSize = (rw_bytes+(additional_Dummy?headerBPP.length:0)) * height;

        int imageDataOffset = 0x36; 
        int fileSize = imageSize + imageDataOffset;

        original_BMP.getPixels(pixels, 0, width, 0, 0, width, height);


        ByteBuffer buffer = ByteBuffer.allocate(fileSize);
        buffer.put((byte)0x42);
        buffer.put((byte)0x4D);
        buffer.put(Int_writer(fileSize));
        buffer.put(Short_writer((short)0));
        buffer.put(Short_writer((short)0));
        buffer.put(Int_writer(imageDataOffset));
        buffer.put(Int_writer(0x28));
        buffer.put(Int_writer(width+(additional_Dummy?(headerBPP.length==3?1:0):0)));
        buffer.put(Int_writer(height));

        //planes
        buffer.put(Short_writer((short)1));
        buffer.put(Short_writer((short)24));
        buffer.put(Int_writer(0));
        buffer.put(Int_writer(imageSize));
        buffer.put(Int_writer(0));
        buffer.put(Int_writer(0));
        buffer.put(Int_writer(0));
        buffer.put(Int_writer(0));

        int row = height;
        int col = width;
        int startPosition = (row - 1) * col;
        int endPosition = row * col;
        
        while( row > 0 ){
            for(int i = startPosition; i < endPosition; i++ ){
                buffer.put((byte)(pixels[i] & 0x000000FF));
                buffer.put((byte)((pixels[i] & 0x0000FF00) >> 8));
                buffer.put((byte)((pixels[i] & 0x00FF0000) >> 16));
            }
            if(additional_Dummy){
                buffer.put(headerBPP);
            }
            row--;
            endPosition = startPosition;
            startPosition = startPosition - col;
        }

        FileOutputStream fos = new FileOutputStream(filePath);
        fos.write(buffer.array());
        fos.close();
        return isSuc;
    }

   
}