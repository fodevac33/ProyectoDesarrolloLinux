<script lang="ts">
  import "../app.pcss";
  import { AppShell, AppBar } from '@skeletonlabs/skeleton';
  import SideBar from "$lib/SideBar.svelte";
</script>


<AppShell>
	<svelte:fragment slot="header">
		<AppBar class="h1 font-bold shadow-lg">Dashboard Sistema Asistido</AppBar>
	</svelte:fragment>
	<svelte:fragment slot="sidebarLeft">
	<SideBar/>
	</svelte:fragment>
	<slot />
</AppShell>
