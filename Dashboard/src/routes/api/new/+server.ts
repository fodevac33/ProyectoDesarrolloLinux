import type { RequestHandler } from './$types';
import type { i2cData } from '$lib/types';
import { prisma } from '$lib/primsa';

export const POST: RequestHandler = async ({request}) => {
    const data = await request.json() as i2cData;    
    const { ambientTemp, motorTemp, latitude, longitude} = data;

    await prisma.data.create({
        data: {
            ambientTemp,
            motorTemp,
            latitude,
            longitude,
        }
    })

    return new Response(JSON.stringify({ message: 'Data processed successfully' }), {
        status: 200,
        headers: {
            'Content-Type': 'application/json'
        }
    });
};