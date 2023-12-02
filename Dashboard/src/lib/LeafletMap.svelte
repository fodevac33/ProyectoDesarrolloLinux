<script lang="ts">
  import { onMount, onDestroy } from 'svelte';
  import { browser } from '$app/environment';
  import type { Map, TileLayer, Marker, LatLngExpression } from 'leaflet';

  let mapElement: HTMLDivElement;
  let map: Map | undefined;

  const center: LatLngExpression= [5.031533638419852,-75.46426814833451];

  onMount(async () => {
    if (browser) {
      const L = await import('leaflet');

      map = L.map(mapElement).setView(center, 16);

      const tileLayer: TileLayer = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      });

      tileLayer.addTo(map);

      const marker: Marker = L.marker(center);
      marker.addTo(map)
        .bindPopup('Mi Moto')
        .openPopup();
    }
  });

  onDestroy(() => {
    map?.remove();
  });
</script>

<div class="m-5 shadow-lg"> 
  <div class="bg-white rounded-lg"> 
    <main>
      <div bind:this={mapElement}></div>
    </main>
  </div>
</div>


<style>
  @import 'leaflet/dist/leaflet.css';
  main div {
      height: 800px;
  }
</style>
