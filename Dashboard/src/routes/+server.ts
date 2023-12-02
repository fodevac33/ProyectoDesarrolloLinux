import type { RequestHandler } from './$types';
import { event } from 'sveltekit-sse'

export const GET: RequestHandler = async () => {
    return new Response();
};