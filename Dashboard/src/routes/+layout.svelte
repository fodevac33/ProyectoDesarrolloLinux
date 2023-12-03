<script lang="ts">
  import "../app.pcss";
  import { AppShell, AppBar } from '@skeletonlabs/skeleton';
  import SideBar from "$lib/SideBar.svelte";
  import type { LayoutData } from "./$types";

  export let data: LayoutData;

  let {sensorData} = data; 
</script>


<AppShell>
	<svelte:fragment slot="header">
		<AppBar class="h1 font-bold shadow-lg">Dashboard Sistema Asistido</AppBar>
	</svelte:fragment>
	<svelte:fragment slot="sidebarLeft">
	<SideBar {...sensorData}/>
	</svelte:fragment>
	<slot />
</AppShell>
