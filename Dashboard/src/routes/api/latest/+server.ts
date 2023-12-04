import { fetchLatestReading } from '$lib/primsa';
import type { RequestHandler } from './$types';

export const GET: RequestHandler = async () => {
    const data = await fetchLatestReading();
    
    return new Response(JSON.stringify(data));
};